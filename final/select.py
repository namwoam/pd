vote = [
    [7, 4, 3, 6, 8, 1, 5, 2],
    [3, 8, 1, 6, 2, 5, 4, 7],
    [1, 3, 2, 5, 8, 4, 6, 7],
    [2, 8, 6, 1, 5, 4, 7, 3],
    [2, 3, 7, 4, 5, 8, 1, 6]
]

result = {}

for i in range(1, 9):
    result[i] = 0
for i in range(len(vote)):
    for k in range(len(vote[i])):
        result[vote[i][k]] += k

print(result)
