console.log(require('fs').readFileSync('./input.txt', 'utf8').split('\n').map(v => v.split(' '))
  .reduce((x, v, i, a) => {
    if (v[0] === '$' && v[1] === 'cd' && v[2] != '..') {
        x[1].push(v[2]);
        x[0].push([x[1].toString().replaceAll(',', '.'), 0]);
    } else if (v[0] === '$' && v[1] === 'cd' && v[2] === '..') {
      const pp = x[1].slice().toString().replaceAll(',', '.');
      x[1].pop();
      x[0][x[0].findIndex(a => a[0] === x[1].toString().replaceAll(',', '.'))][1] += x[0][x[0].findIndex(a => a[0] === pp)][1];
    } else if (parseInt(v[0])) {
      x[0][x[0].length-1][1] += parseInt(v[0]);
    }
    if (i === a.length-1) {
      Array(x[1].length-1).fill().map((_, i) => {
        const pp = x[1].slice().toString().replaceAll(',', '.');
        x[1].pop();
        x[0][x[0].findIndex(a => a[0] === x[1].toString().replaceAll(',', '.'))][1] += x[0][x[0].findIndex(a => a[0] === pp)][1];
      })
    }
    return x;
  }, [[], []])
  .reduce((x, v, i) => i === 0 ? v : x, [])
  .reduce((x, v) => x + (v[1] <= 100000 ? v[1] : 0), 0)
);

console.log(require('fs').readFileSync('./input.txt', 'utf8').split('\n').map(v => v.split(' '))
  .reduce((x, v, i, a) => {
    if (v[0] === '$' && v[1] === 'cd' && v[2] != '..') {
        x[1].push(v[2]);
        x[0].push([x[1].toString().replaceAll(',', '.'), 0]);
    } else if (v[0] === '$' && v[1] === 'cd' && v[2] === '..') {
      const pp = x[1].slice().toString().replaceAll(',', '.');
      x[1].pop();
      x[0][x[0].findIndex(a => a[0] === x[1].toString().replaceAll(',', '.'))][1] += x[0][x[0].findIndex(a => a[0] === pp)][1];
    } else if (parseInt(v[0])) {
      x[0][x[0].length-1][1] += parseInt(v[0]);
    }
    if (i === a.length-1) {
      Array(x[1].length-1).fill().map((_, i) => {
        const pp = x[1].slice().toString().replaceAll(',', '.');
        x[1].pop();
        x[0][x[0].findIndex(a => a[0] === x[1].toString().replaceAll(',', '.'))][1] += x[0][x[0].findIndex(a => a[0] === pp)][1];
      })
    }
    return x;
  }, [[], []])
  .reduce((x, v, i) => i === 0 ? v : x, [])
  .filter((v, i, a) => v[1] + 70000000 - a[0][1] >= 30000000)
  .map(v => v[1])
  .sort((a, b) => a-b)[0]
);
