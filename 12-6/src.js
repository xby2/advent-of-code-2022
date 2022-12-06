console.log(require('fs').readFileSync('./input.txt', 'utf8').split('')
  .map((_, i, a) => i >= 4 ? new Set(a.slice(i-4, i)).size === 4 | 0 : 0 )
  .indexOf(1)
);

console.log(require('fs').readFileSync('./input.txt', 'utf8').split('')
  .map((_, i, a) => i >= 14 ? new Set(a.slice(i-14, i)).size === 14 | 0 : 0 )
  .indexOf(1)
);