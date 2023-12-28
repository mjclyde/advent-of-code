const fs = require('fs')

const file = fs.readFileSync('./input.txt', 'utf8')
const MAX = {
	red: 12,
	green: 13,
	blue: 14,
}

let sum = 0;
file.split('\n').forEach(line => {
	const match = /Game (\d*):/gi.exec(line)
	if (!match || !match[1]) { return }
	let noGood = false;
	line.substr(match[0].length).split(';').forEach(rawRound => {
		const round = { red: 0, green: 0, blue: 0 }
		rawRound.split(',').forEach(cubes => {
			const m = /(\d+) (red|blue|green)/gi.exec(cubes);
			if (!m || !m[1]) { return }
			round[m[2]] = +m[1]
			if (round[m[2]] > MAX[m[2]]) {
				noGood = true
				return false;
			}
		})
		if (noGood) {
			return false;
		}
	})
	if (!noGood) {
		sum += +match[1]
	}
})

console.log(sum)

