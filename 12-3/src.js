console.log(require('fs')
    .readFileSync('./input.txt', 'utf8')
    .split(/\s+/)
    .map(v => v.split(''))
    .map(v => v.slice(0, v.length/2).filter(a => v.slice(v.length/2).includes(a))[0])
    .map(v => 65 <= v.charCodeAt(0) && v.charCodeAt(0) <= 90 ? v.charCodeAt(0) - 38 : v.charCodeAt(0) - 96)
    .reduce((x, v) => x+v, 0));

console.log(require('fs')
    .readFileSync('./input.txt', 'utf8')
    .split(/\s+/)
    .reduce((x, v, i) => { i%3===0 ? x.push([v]) : x[Math.floor(i/3.0)].push(v); return x; }, [])
    .map(v => v[0].split('').filter(a => v[1].split('').filter(b => v[2].split('').includes(b)).includes(a))[0])
    .map(v => 65 <= v.charCodeAt(0) && v.charCodeAt(0) <= 90 ? v.charCodeAt(0) - 38 : v.charCodeAt(0) - 96)
    .reduce((x, v) => x+v, 0));