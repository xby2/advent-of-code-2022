console.log(require('fs').readFileSync('./input.txt', 'utf8').split('\r\n')
  .reduce((x, v) => { v==='' ? x.push([]) : x[x.length-1].push(parseInt(v)); return x; }, [[]])
  .map(v => v.reduce((x, v) => x+v, 0))
  .sort((a, b) => b-a)
  .reduce((x, v, i) => x + (i === 0 ? v : 0), 0));

console.log(require('fs').readFileSync('./input.txt', 'utf8').split('\r\n')
  .reduce((x, v) => { v==='' ? x.push([]) : x[x.length-1].push(parseInt(v)); return x; }, [[]])
  .map(v => v.reduce((x, v) => x+v, 0))
  .sort((a, b) => b-a)
  .reduce((x, v, i) => x + (i < 3 ? v : 0), 0));