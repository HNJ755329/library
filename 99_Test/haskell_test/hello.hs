{-# LANGUAGE TypeApplications #-}
{-# LANGUAGE LambdaCase, DeriveFunctor #-}

import           Control.Applicative
import           Control.Arrow
import           Control.Monad
import           Data.Bits
import           Data.Char
import           Data.List
import           Data.Maybe
import           Data.Ord
import           Control.Monad.Fix
import qualified Data.Set                      as S

area r = pi * square r
　where
    pi = 3.14
    square x = x * x

main :: IO()
main = do
    putStrLn $ "HELLO WORLD"
    print $ even 0
    print $ area 10
    print $ sum $ map (\x->x*x) [1..10]
    print $ [x | x <- [1..10], even x]
    print $ (+5) <$> [5,8]
    print $ (*5) <$> take 10 [1,2..]
    print $ (+9) <$> (Just 5)
    print $ (+9) <$> Nothing
    print $ (\x->x+1) <$> (Just 11)
    x <- getLine
    print x
    -- s <- getLine
    -- putStrLn $ if last s == 's' then s ++ "es" else s ++ "s"
