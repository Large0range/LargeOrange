#![allow(non_snake_case)]

mod keywordCallbacks;

use std::fs;
use std::collections::HashMap;

use regex::Regex;

//Regex::new(r"(\[\w+\])").unwrap(); -> Regex matcher for the variables

fn remember(args: &[&str], Hash: &mut HashMap<String, String>) { // function for the remember instruction
    Hash.insert(args[0].to_string(), args[1].to_string()); // insert variable name and value into hash map 
}


fn say(args: &[&str], _Hash: &mut HashMap<String, String>) { // function for telling the computer to output something
    let joined = args.join(" "); // join the following arguments passed to the say instruction
    
    
    println!("{}", joined); //output the final string
}

fn add(args: &[&str], Hash: &mut HashMap<String, String>) {
    let variableName = args[0]; // get the variable to store the output in 
    
    let int1 = args[1].parse::<i32>().unwrap(); // get the first number, parse and unwrap both
    let int2 = args[2].parse::<i32>().unwrap(); // get the second number

    Hash.insert(variableName.to_string(), (int1+int2).to_string());
}

fn sub(args: &[&str], Hash: &mut HashMap<String, String>) {
    let variableName = args[0]; // get the variable to store the output in 
    
    let int1 = args[1].parse::<i32>().unwrap(); // get the first number, parse and unwrap both
    let int2 = args[2].parse::<i32>().unwrap(); // get the second number


    Hash.insert(variableName.to_string(), (int1-int2).to_string());
}

fn mul(args: &[&str], Hash: &mut HashMap<String, String>) {
    let variableName = args[0]; // get the variable to store the output in 
    
    let int1 = args[1].parse::<i32>().unwrap(); // get the first number, parse and unwrap both
    let int2 = args[2].parse::<i32>().unwrap(); // get the second number


    Hash.insert(variableName.to_string(), (int1*int2).to_string());
}

fn div(args: &[&str], Hash: &mut HashMap<String, String>) {
    let variableName = args[0]; // get the variable to store the output in 
    
    let int1 = args[1].parse::<i32>().unwrap(); // get the first number, parse and unwrap both
    let int2 = args[2].parse::<i32>().unwrap(); // get the second number


    Hash.insert(variableName.to_string(), (int1/int2).to_string());    
}

fn CreateHashMap() -> HashMap<String, fn(&[&str], &mut HashMap<String, String>)> { //create the hash map for instruction to function saving
    let TokenHashMap: HashMap<String, fn(&[&str], &mut HashMap<String, String>)> = HashMap::from([
        ("remember".to_string(), remember as fn(&[&str], &mut HashMap<String, String>)), // remember instruction
        ("say".to_string(), say as fn (&[&str], &mut HashMap<String, String>)),          // say instruction
        ("add".to_string(), add as fn(&[&str], &mut HashMap<String, String>)), // add instruction
        ("sub".to_string(), sub as fn(&[&str], &mut HashMap<String, String>)), // sub instruction
        ("mul".to_string(), mul as fn(&[&str], &mut HashMap<String, String>)), // mul instruction
        ("div".to_string(), div as fn(&[&str], &mut HashMap<String, String>)), // div instruction
    ]);

    return TokenHashMap;
}


fn main() {
    let args: Vec<String> = std::env::args().collect();
    if args.len() == 1 { std::process::exit(1); } //make sure user passed some file 

    let sourceCode = fs::read_to_string(&args[1]).expect("Could not read file"); // read the file into a string

    let TokenHashMap = CreateHashMap(); // create the hash map 
    let mut VariableHashMap: HashMap<String, String> = HashMap::new();


    let clean = sourceCode.replace("\n", "").replace("\r", ""); // purge new lines, and the fucking carriage returns cuz windows is just retarded
    let splitCode = clean.split(";"); // split the code by ;

    let RegexMatch = Regex::new(r"(\[\w+\])").unwrap(); // Create the regex matcher for the iterator that finds variable names in the lines

    for mut line in splitCode { // loop through each line in the source code
        if line.len() == 0 { continue; } //if the line is empty then just continue
        if line.starts_with("//") { continue; } // LINE ACCOUNTS FOR COMMENTS


        let iter = RegexMatch.find_iter(&line); // get all instances of [VARIABLE_NAME]
    
        let mut fixed = "".to_string(); // create a dummy string

        //Loop over every found variable name
        for l in iter { // iterate over each instance of a word in square brackets
            let variableReplacement = l.as_str(); // get the actual string found
            let variableName = variableReplacement.replace("[", "").replace("]", ""); // purge the square brackets from the string
            match VariableHashMap.get(&variableName) { // hashmap lookup for the variable name inside the square brackets
                Some(S) => fixed = line.replace(&variableReplacement, S), // set dummy string fixed to join modified with the variable value
                None => (), // handle none
            }
        } 

        if !fixed.is_empty() { line = &fixed; } //avoid having a random empty string that then gets parsed 

        let mut words = line.split(" "); // split the code by spaces
        
        let Some(S) = words.nth(0) else { return () }; // Get the string of the first element of the split line 

        match TokenHashMap.get(&S.to_string()) {  //match the first word to a keyword in the hashmap
            Some(t) => {
                            let instructionArguments: Vec<&str> = (&mut words).skip(0).collect(); // get the arguments after the initial instruction
                            let x = &mut VariableHashMap; // declare a mutable reference to the variable hash map
                            t(&instructionArguments, x); // pass following arguments and variable hash map to the instruction function
                        },
            None => panic!("Unknown instruction, {}", &S), // if instruction does not exist then panic
        }
    }
}
