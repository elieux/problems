import sys

if (len(sys.argv) != 4):
	print("usage: {0} [letters] [start] [end]".format(sys.argv[0]))
	sys.exit(1)

letters = sys.argv[1]
start = int(sys.argv[2]) - 1
end = int(sys.argv[3]) - 1
assert(start <= end)

expected = list(letters)
order = 1
while len(expected) < end:
	smallers = expected[-(len(letters) ** order):]
	for letter in letters:
		expected.extend((letter + smaller for smaller in smallers))
	order += 1

case = []
case.append(str(end - start))
for i in range(start, end):
	case.append(letters + ' ' + str(i + 1))

with open('generated.in', 'w', encoding = 'utf-8') as file:
	for line in case:
		file.write(line)
		file.write('\n')

with open('generated.out', 'w') as file:
	for i, line in enumerate(expected[start:end]):
		file.write('Case #' + str(i + 1) + ': ' + line)
		file.write('\n')
