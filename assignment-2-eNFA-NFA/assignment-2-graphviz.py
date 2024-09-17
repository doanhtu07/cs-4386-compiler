from graphviz import Digraph

# === Nodes ===
nodes = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N"]
final = set(["A", "E", "F", "G", "H", "I", "K", "L", "M", "N"])

# === Edges ===
edges = set(
    [
        ("C", "E", 0),
        ("D", "F", 1),
        ("J", "L", 0),
        ("A", "E", 0),
        ("A", "L", 0),
        ("A", "F", 0),
        ("B", "E", 0),
        ("B", "F", 1),
        ("E", "E", 0),
        ("E", "F", 1),
        ("E", "L", 0),
        ("F", "E", 0),
        ("F", "F", 1),
        ("F", "L", 0),
        ("G", "E", 0),
        ("G", "F", 1),
        ("G", "L", 0),
        ("H", "L", 0),
        ("I", "L", 0),
    ]
)

source0 = ["E", "A", "B", "G", "F"]
source1 = ["F", "A", "B", "G", "E"]
target = ["G", "B", "C", "D", "H", "I", "J", "K", "M", "N"]

for source in source0:
    for t in target:
        edges.add((source, t, 0))

for source in source1:
    for t in target:
        edges.add((source, t, 1))

source0 = ["J", "A", "E", "G", "H", "I", "F"]
target = ["L", "N"]

for source in source0:
    for t in target:
        edges.add((source, t, 0))

edges = list(edges)
edges.sort()

# DEBUG
# print(edges)

# === Graph ===

# Create a new directed graph
dot = Digraph(engine="dot")

# Add nodes to graph
for node in nodes:
    if node in final:
        dot.node(node, shape="doublecircle", width="1", height="1")
    else:
        dot.node(node, shape="circle", width="1", height="1")

# Add edges with weights
for edge in edges:
    edge_color = "blue" if edge[2] == 0 else "red"
    dot.edge(
        edge[0],
        edge[1],
        label=str(edge[2]),
        fontsize="20",
        color=edge_color,
    )

# Render the graph to a file and display it
dot.render("graph", format="png", view=True)
