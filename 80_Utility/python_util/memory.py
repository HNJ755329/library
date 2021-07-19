import objgraph
"""
objgraphを使ってオブジェクト間の関係図を図示する。
メモリ管理に役立つ（かも）
"""


def example():
    x = []
    y = [x, [x], dict(x=x)]
    objgraph.show_refs(
        (x, y),
        filename='show_refs.png', 
        refcounts=True
    )
    objgraph.show_backrefs(
        (x, y),
        filename='show_backrefs.png', 
        refcounts=True
    )

if __name__ == "__main__":
    example()
