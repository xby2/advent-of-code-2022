const ROCK = 1;
const PAPER = 2;
const SCISSORS = 3;

const WIN = 6;
const DRAW = 3;
const LOSE = 0;

const q1answers = {
  'A': {
    'X': ROCK + DRAW,
    'Y': PAPER + WIN,
    'Z': SCISSORS + LOSE
  },
  'B': {
    'X': ROCK + LOSE,
    'Y': PAPER + DRAW,
    'Z': SCISSORS + WIN
  },
  'C': {
    'X': ROCK + WIN,
    'Y': PAPER + LOSE,
    'Z': SCISSORS + DRAW
  },
};

const q2answers = {
  'A': {
    'X': SCISSORS + LOSE,
    'Y': ROCK + DRAW,
    'Z': PAPER + WIN
  },
  'B': {
    'X': ROCK + LOSE,
    'Y': PAPER + DRAW,
    'Z': SCISSORS + WIN
  },
  'C': {
    'X': PAPER + LOSE,
    'Y': SCISSORS + DRAW,
    'Z': ROCK + WIN
  },
};

console.log(require('fs').readFileSync('./input.txt', 'utf8').split('\r\n')
  .map(v => q1answers[v.split(' ')[0]][v.split(' ')[1]])
  .reduce((x, a) => x + a, 0));

console.log(require('fs').readFileSync('./input.txt', 'utf8').split('\r\n')
  .map(v => q2answers[v.split(' ')[0]][v.split(' ')[1]])
  .reduce((x, a) => x + a, 0));