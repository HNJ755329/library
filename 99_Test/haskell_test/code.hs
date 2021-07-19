{-# LANGUAGE
  ScopedTypeVariables, BangPatterns, TupleSections, ExplicitForAll,
  LambdaCase, MultiWayIf, Unsafe, RecordWildCards, FlexibleContexts, CPP,
  NoMonomorphismRestriction, GADTs, PatternGuards, MagicHash, UnboxedTuples,
  RankNTypes, EmptyDataDecls, EmptyCase, ViewPatterns, PolyKinds,
  TypeFamilies, OverloadedStrings, FlexibleInstances, UndecidableInstances,
  DefaultSignatures, GeneralizedNewtypeDeriving, StandaloneDeriving,
  DeriveGeneric, DeriveFunctor, DeriveDataTypeable, DeriveFoldable,
  DeriveTraversable, DeriveDataTypeable, FlexibleInstances,
  MultiParamTypeClasses #-}
{-# OPTIONS_GHC -O2 #-}

import Prelude
import Data.Bits
import Data.List
import Data.Maybe
import Data.Tuple
import Data.Ord
import Data.Int
import Data.Word
import Data.Char
import Data.Ratio
import Data.Function
import Data.STRef
import Data.IORef
import Data.Monoid
import Data.Functor
import Data.Data
import Data.Typeable
import GHC.Generics
import System.IO
import Control.Arrow
import Control.Applicative
import Control.Monad
import Control.Monad.Primitive
import Control.Monad.State.Strict
import Control.Monad.ST
import Control.Monad.ST.Lazy (strictToLazyST, lazyToStrictST)
import qualified Control.Monad.ST.Lazy as STL
-- import Control.Monad.ST.Safe
import Control.DeepSeq
import Data.Coerce
import qualified Data.ByteString.Char8 as BS
import qualified Data.ByteString.Lazy.Char8 as BSL
import qualified Data.ByteString.Builder as BSB
import Data.IntMap (IntMap)
import qualified Data.IntMap.Strict as IMS
import qualified Data.IntMap.Lazy as IML
import Data.IntSet (IntSet)
import qualified Data.IntSet as IS
import qualified Data.Sequence as Seq
import Data.Sequence (Seq)
import qualified Data.Array.IArray as A
import qualified Data.Array.MArray.Safe as A
import qualified Data.Array.MArray as A
import Data.Array (Array)
import Data.Array.Unboxed (UArray)
import Data.Array.IArray (IArray)
import Data.Array.MArray.Safe (MArray)
import Data.Array.IO.Safe (IOArray, IOUArray)
import Data.Array.ST.Safe (STArray, STUArray, runSTArray, runSTUArray)
import qualified Data.Vector as V
import qualified Data.Vector.Mutable as VM
import qualified Data.Vector.Unboxed as VU
import qualified Data.Vector.Unboxed.Mutable as VUM
import qualified Data.Vector.Storable as VS
import qualified Data.Vector.Storable.Mutable as VSM
import qualified Data.Vector.Primitive as VP
import qualified Data.Vector.Primitive.Mutable as VPM
import qualified Data.Vector.Generic as VG
import qualified Data.Vector.Generic.Mutable as VGM
import qualified Data.Vector.Fusion.Bundle.Monadic as VFBM
import qualified Data.Vector.Fusion.Bundle as VFB
import qualified Data.Vector.Fusion.Stream.Monadic as VFSM
import qualified Data.Vector.Fusion.Bundle.Size as VFBS
import qualified Data.Vector.Fusion.Util as VFU
import qualified Data.Attoparsec.ByteString.Char8 as Atto
import Debug.Trace
import GHC.Exts (build, Int(..), Int#,
                 (+#), (*#), (-#), (<#), (>=#), (==#), quotRemInt#,
                 remInt#, uncheckedIShiftRL#, andI#, orI#,
                isTrue#)

main :: IO ()
main = do
  n <- readInt <$> getLine
  songs <- V.replicateM n $ do
    [x,y] <- words <$> getLine
    return (x,readInt y)
  x <- getLine
  let rest = V.tail $ V.dropWhile ((/=x) . fst) songs
  print $ V.sum $ V.map snd rest
  return ()

#define IL(f) {-# INLINE f #-}; f

IL(putBuilder) = BSB.hPutBuilder stdout

printVecInLines, printVecInSpcSepLn ::
  (VG.Vector v a, ShowAsBuilder a) => v a -> IO ()
IL(printVecInLines) = putBuilder . v2BLines
IL(printVecInSpcSepLn) = putBuilder . v2BSpcSepLn

class ShowAsBuilder a where
  showAsBuilder :: a -> BSB.Builder
  default showAsBuilder :: (Show a) => a -> BSB.Builder
  showAsBuilder = BSB.string8 . show

-- Inconsistent with show
instance (ShowAsBuilder a, VG.Vector v a) => ShowAsBuilder (v a) where
  IL(showAsBuilder) = v2BSpcSep

#define INS(t,f) instance ShowAsBuilder t where { IL(showAsBuilder)=f }
INS(Int,BSB.intDec)
INS(Int8,BSB.int8Dec)
INS(Int16,BSB.int16Dec)
INS(Int32,BSB.int32Dec)
INS(Int64,BSB.int64Dec)
INS(Word,BSB.wordDec)
INS(Word8,BSB.word8Dec)
INS(Word16,BSB.word16Dec)
INS(Word32,BSB.word32Dec)
INS(Word64,BSB.word64Dec)
INS(Integer,BSB.integerDec)
INS(Float,BSB.floatDec)
INS(Double,BSB.doubleDec)
-- INS(String,BSB.string8) -- Inconsistent with Show
-- INS(BS.ByteString,BSB.byteString) -- Inconsistent with Show
-- INS(BSL.ByteString,BSB.lazyByteString) -- Inconsisitent with Show
#undef INS

-- Inconsistent with Show
instance (ShowAsBuilder a, ShowAsBuilder b) => ShowAsBuilder (a,b) where
  IL(showAsBuilder) = showTupAsBuilder
instance (ShowAsBuilder a, ShowAsBuilder b, ShowAsBuilder c) =>
  ShowAsBuilder (a,b,c) where
  IL(showAsBuilder) = showTup3AsBuilder
instance (ShowAsBuilder a, ShowAsBuilder b, ShowAsBuilder c, ShowAsBuilder d) =>
  ShowAsBuilder (a,b,c,d) where
  IL(showAsBuilder) = showTup4AsBuilder

IL(showTupAsBuilderWith)
  :: (a -> BSB.Builder) -> (b -> BSB.Builder) -> (a,b) -> BSB.Builder
showTupAsBuilderWith showA showB
  = \(a,b) -> (showA a <>) $ BSB.char7 ' ' <> showB b
IL(showTupAsBuilder) :: (ShowAsBuilder a, ShowAsBuilder b)
  => (a,b) -> BSB.Builder
showTupAsBuilder = showTupAsBuilderWith showAsBuilder showAsBuilder 

IL(showTup3AsBuilderWith) :: (a -> BSB.Builder) -> (b -> BSB.Builder) ->
  (c -> BSB.Builder) -> (a,b,c) -> BSB.Builder
showTup3AsBuilderWith showA showB showC
  = \(a,b,c) -> (showA a <>) $ (BSB.char7 ' ' <>) $ (showB b <>)
                $ (BSB.char7 ' ' <>) $ showC c
IL(showTup3AsBuilder) :: (ShowAsBuilder a, ShowAsBuilder b, ShowAsBuilder c)
  => (a,b,c) -> BSB.Builder
showTup3AsBuilder
  = showTup3AsBuilderWith showAsBuilder showAsBuilder showAsBuilder

IL(showTup4AsBuilderWith) :: (a -> BSB.Builder) -> (b -> BSB.Builder) ->
  (c -> BSB.Builder) -> (d -> BSB.Builder) -> (a,b,c,d) -> BSB.Builder
showTup4AsBuilderWith showA showB showC showD
  = \(a,b,c,d) -> (showA a <>) $ (BSB.char7 ' ' <>)
                  $ showTup3AsBuilderWith showB showC showD (b,c,d)
IL(showTup4AsBuilder) ::
  (ShowAsBuilder a, ShowAsBuilder b, ShowAsBuilder c, ShowAsBuilder d) =>
  (a,b,c,d) -> BSB.Builder
showTup4AsBuilder = showTup4AsBuilderWith showAsBuilder showAsBuilder
                    showAsBuilder showAsBuilder

v2BSpcSepLn, v2BSpcSep, v2BConcat, v2BLines ::
  (VG.Vector v a, ShowAsBuilder a)
  => v a -> BSB.Builder
IL(v2BSpcSepLn) = v2BSpcSepLnWith showAsBuilder
IL(v2BSpcSep) = v2BSpcSepWith showAsBuilder
IL(v2BConcat) = v2BConcatWith showAsBuilder
IL(v2BLines) = v2BLinesWith showAsBuilder


v2BSpcSepLnWith, v2BSpcSepWith, v2BConcatWith, v2BLinesWith ::
  (VG.Vector v a)
  => (a -> BSB.Builder) -- ^ show function
  -> v a -> BSB.Builder
IL(v2BSpcSepLnWith) = v2BSpcSepPostfWith $ BS.singleton '\n'
IL(v2BSpcSepWith) = v2BSpcSepPostfWith BS.empty
IL(v2BConcatWith) showFct = VG.foldr ((<>) . showFct) mempty
IL(v2BLinesWith) showFct
  = VG.foldr (\ a -> (showFct a <>) . (BSB.char7 '\n' <>)) mempty


v2BSpcSepPostf :: (VG.Vector v a, ShowAsBuilder a)
  => BS.ByteString -- ^ postfix
  -> v a -> BSB.Builder
IL(v2BSpcSepPostf) = (`v2BSpcSepPostfWith` showAsBuilder)

v2BSpcSepPostfWith :: (VG.Vector v a)
  => BS.ByteString -- ^ postfix
  -> (a -> BSB.Builder) -- ^ show function
  -> v a -> BSB.Builder
IL(v2BSpcSepPostfWith) = vecToBuilder BS.empty $ BS.singleton ' '

IL(vecToBuilder) :: (VG.Vector v a)
  => BS.ByteString -- ^ prefix
  -> BS.ByteString -- ^ separator
  -> BS.ByteString -- ^ postfix
  -> (a -> BSB.Builder) -- ^ show function
  -> v a -> BSB.Builder
vecToBuilder !prefix !separator !postfix
  = vecToBuilder_ (BSB.byteString prefix)
                  (BSB.byteString separator)
                  (BSB.byteString postfix)


IL(vecToBuilder_) :: (VG.Vector v a)
  => BSB.Builder -- ^ prefix
  -> BSB.Builder -- ^ separator
  -> BSB.Builder -- ^ postfix
  -> (a -> BSB.Builder) -- ^ show function
  -> v a -> BSB.Builder
vecToBuilder_ !prefix !separator !postfix showFct = \vec -> prefix <>
  VG.foldr
  (\ a rest !prefx -> prefx <> (showFct a <> rest separator))
  (const postfix) vec mempty

IL(evalVals) :: [a] -> [a]
evalVals xs = build $ \c n -> foldr (c $!) n xs
IL(forceVals) :: (NFData a) => [a] -> [a]
forceVals xs = build $ \c n -> foldr (c $!!) n xs

IL(getVecGLn) :: (VG.Vector v a) =>
  Int -> StateT BS.ByteString Maybe a -> IO (v a)
getVecGLn n s = VG.unfoldrN n (runStateT s) <$> BS.getLine
IL(getVecGRest) :: (VG.Vector v a) =>
  Int -> StateT BSL.ByteString Maybe a -> IO (v a)
getVecGRest n s = VG.unfoldrN n (runStateT s) <$> BSL.getContents
IL(getVecLn) :: Int -> StateT BS.ByteString Maybe a -> IO (V.Vector a)
getVecLn = getVecGLn
IL(getVecRest) :: Int -> StateT BSL.ByteString Maybe a -> IO (V.Vector a)
getVecRest = getVecGRest
IL(getVecULn) :: (VU.Unbox a) =>
  Int -> StateT BS.ByteString Maybe a -> IO (VU.Vector a)
getVecULn = getVecGLn
IL(getVecURest) :: (VU.Unbox a) =>
  Int -> StateT BSL.ByteString Maybe a -> IO (VU.Vector a)
getVecURest = getVecGRest

rInt :: StateT BSL.ByteString Maybe Int
IL(rInt) = StateT $ BSL.readInt . BSL.dropWhile (<'!')
rIntS :: StateT BS.ByteString Maybe Int
IL(rIntS) = StateT $ BS.readInt . BS.dropWhile (<'!')

unlessM, whenM :: (Monad m) => m Bool -> m () -> m ()
IL(whenM) = (. flip when) . (>>=)
IL(unlessM) = (. flip unless) . (>>=)

IL(wrA) = A.writeArray
IL(rdA) = A.readArray
IL(mdA) = \arr f !i -> do
  ai <- rdA arr i
  let fai = f ai 
  wrA arr i fai
  return (ai,fai)
{-# INLINE mdA' #-}
mdA' = \arr f !i -> do
  !ai <- rdA arr i
  let !fai = f ai
  wrA arr i fai
  return (ai,fai)
IL(swapA) = \arr !i !j -> do
  ai <- rdA arr i
  wrA arr i =<< rdA arr j
  wrA arr j ai

#define D(f,r,d)\
  IL(f) :: Integral a=>a->d; f=fromIntegral;\
  IL(r) :: String->d; r=read
#define C(f,r,g,h,d) D(f,r,d);\
  g,h :: RealFrac a=>a->d; IL(g)=floor; IL(h)=ceiling
C(_toInteger_,readInteger,floorInteger,ceilInteger,Integer)
C(toInt,readInt,floorInt,ceilInt,Int)
C(toI8,readI8,floorI8,ceilI8,Int8)
C(toI16,readI16,floorI16,ceilI16,Int16)
C(toI32,readI32,floorI32,ceilI32,Int32)
C(toI64,readI64,floorI64,ceilI64,Int64)
C(toWord,readWord,floorWord,ceilWord,Word)
C(toW8,readW8,floorW8,ceilW8,Word8)
C(toW16,readW16,floorW16,ceilW16,Word16)
C(toW32,readW32,floorW32,ceilW32,Word32)
C(toW64,readW64,floorW64,ceilW64,Word64)
D(toDouble,readDouble,Double)
D(toFloat,readFloat,Float)
#undef D
#undef C

#define N(f,g,h,a,m)\
  IL(f) :: forall e i s. (C(a,m)A.Ix i) => (i,i) -> e -> m (a i e);\
  f=A.newArray;\
  IL(g) :: forall e i s. (C(a,m)A.Ix i) => (i,i) -> m (a i e);\
  g=A.newArray_;\
  IL(h) :: forall e i s. (C(a,m)A.Ix i) => (i,i) -> [e] -> m (a i e);\
  h=A.newListArray
#define C(a,m)
N(newIOA,newIOA_,newIOAL,IOArray,IO)
N(newSTA,newSTA_,newSTAL,STArray s,ST s)
#undef C
#define C(a,m) MArray (a) e (m), 
N(newIOUA,newIOUA_,newIOUAL,IOUArray,IO)
N(newSTUA,newSTUA_,newSTUAL,STUArray s,ST s)
#undef C
#undef N

#undef IL
