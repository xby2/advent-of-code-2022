use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

fn main() {

    let mut most_calories = 0;
    let mut total_calories = 0;

    if let Ok(lines) = read_lines("./input.txt") {
        for line in lines {
            if let Ok(calories: i64) = line {
                
            }
        }
    }
}