console.log(require('fs').readFileSync('./input.txt', 'utf8').split('\n')
  .reduce((x, v, i) => {
    if (v.charAt(0) === '[') {
      x.map((_, j) => { if (v[4*j+1] != ' ') x[j].unshift(v[4*j+1]) })
    } else if (v.charAt(0) === 'm') {
      Array(parseInt(v.split(' ')[1])).fill().map((_, k) => x[parseInt(v.split(' ')[5])-1].push(x[parseInt(v.split(' ')[3])-1].pop()))
    }
    return x;
  }, [[],[],[],[],[],[],[],[],[]])
  .map(v => v[v.length-1])
);

console.log(require('fs').readFileSync('./input.txt', 'utf8').split('\n')
  .reduce((x, v, i) => {
    if (v.charAt(0) === '[') {
      x.map((_, j) => { if (v[4*j+1] != ' ') x[j].unshift(v[4*j+1]) })
    } else if (v.charAt(0) === 'm') {
      const temp = [];
      Array(parseInt(v.split(' ')[1])).fill().map((_, k) => temp.push(x[parseInt(v.split(' ')[3])-1].pop()))
      Array(parseInt(v.split(' ')[1])).fill().map((_, k) => x[parseInt(v.split(' ')[5])-1].push(temp.pop()))
    }
    return x;
  }, [[],[],[],[],[],[],[],[],[]])
  .map(v => v[v.length-1])
);
