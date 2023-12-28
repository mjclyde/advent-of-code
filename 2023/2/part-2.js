const fs = require('fs')

const file = fs.readFileSync('./input.txt', 'utf8')

let sum = 0;
file.split('\n').forEach(line => {

	const match = /Game (\d*):/gi.exec(line)
	if (!match || !match[1]) { return }
	const max = {
		red: 0,
		green: 0,
		blue: 0,
	}

	line.substr(match[0].length).split(';').forEach(rawRound => {

		const round = { red: 0, green: 0, blue: 0 }
		rawRound.split(',').forEach(cubes => {

			const m = /(\d+) (red|blue|green)/gi.exec(cubes);
			if (!m || !m[1]) { return }
			round[m[2]] = +m[1]

			if (round[m[2]] > max[m[2]]) {
				max[m[2]] = round[m[2]]
			}

		})

	})

	sum += max.red * max.green * max.blue

})

console.log(sum)

