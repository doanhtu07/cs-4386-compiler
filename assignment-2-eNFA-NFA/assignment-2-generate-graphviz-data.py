nodes = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N"]

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

print("Nodes:", len(edges))

print("start -> A")
print("start [shape=Mdiamond]")
print("end [shape=Msquare]")

for i, edge in enumerate(edges):
    print(edge[0], "->", edge[1], f"[weight={edge[2]}]")
