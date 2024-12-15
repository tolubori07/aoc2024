file = open("input.txt","r")
left = []
right = []

for line in file:
    left.append(line[0:5].strip())
    right.append(line[8:13].strip())

left =[int(x) for x in left if x]
right =[int(x) for x in right if x]
left.sort()
right.sort()
if len(left) != len(right):
    print("Error: The lists 'left' and 'right' have different lengths.")
total = 0
for i in range(len(left)):
    total += abs(left[i]-right[i])
print(total)
file.close()
