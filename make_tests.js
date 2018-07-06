#!/usr/bin/node 
const fs = require('fs')
const { execSync } = require('child_process')
const resultDir = './bin/'


Array.prototype.flatten = function() {
	const result = []

	for (const element of this) {
		if (Array.isArray(element))
			for (const e of element)
				result.push(e)
		else
			result.push(element)
	}

	return result
}


function compile(files, result, additional = '-c') {
  function callback(error, stdout, stderr) {
		if (stdout) console.log(stdout)
		if (stderr) {
			console.error(stderr)
			if (fs.existsSync(result))
				fs.unlinkSync(result)

			process.exit(1)
		}
	}
    
	execSync(`g++ -std=c++1z -Wall -Wextra -pedantic ${files} -o ${result} ${additional}`, callback)
}

const compareDate = (lhs, array) =>
	array.filter(rhs => new Date(fs.lstatSync(lhs).mtime) < new Date(fs.lstatSync(rhs).mtime))
	.length == 0

const processDirectory = dirname => {
	const dirContent = fs.readdirSync(dirname)
	return dirContent.filter(x => x.includes('hpp'))
		.map(headerFile => {
			const name = headerFile.split('.hpp')[0]
			const codeFile = dirname + name + '.cpp'
			const result = resultDir + name + '.o'
			if (fs.existsSync(codeFile)) {
				if (!fs.existsSync(result) || !compareDate(result, [codeFile, dirname + headerFile]))
          compile(codeFile, result)
          
				return result
			}
		})
		.filter(module => !!module)
}

(function(){
  const modules = ['io_handling', 'json++', 'json++/print']
    .map(x => `./${x}/`)
    .map(processDirectory)
    .flatten()

  compile(modules.join(' ') + ' test.cpp', 'jpp-test', '-Wl,-Bdynamic -L/usr/local/lib -lboost_unit_test_framework')
})()
