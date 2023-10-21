#![allow(non_snake_case)]

mod keywordCallbacks;

use std::fs;
use std::collections::HashMap;

use regex::Regex;

//Regex::new(r"(\[\w+\])").unwrap(); -> Regex matcher for the variables

fn remember(args: &[&str], Hash: &mut HashMap<String, String>) { // function for the remember instruction
    Hash.insert(args[0].to_string(), args[1].to_string()); // insert variable name and value into hash map 
}

fn say(args: &[&str], Hash: &mut HashMap<String, String>) { // function for telling the computer to output something
    let mut joined = args.join(" "); // join the following arguments passed to the say instruction
    
    let RegexMatch = Regex::new(r"(\[\w+\])").unwrap(); // create a regex matcher for any word within square brackets
    let iter = RegexMatch.find_iter(&joined); // get all instances of this

    let mut fixed = "".to_string(); // create a dummy string for scoping reasons

    //BLOCK ALLOWS FOR VARIABLE OUTPUT
    for l in iter { // iterate over each instance of a word in square brackets
        let variableReplacement = l.as_str(); // get the actual string found
        let variableName = variableReplacement.replace("[", "").replace("]", ""); // purge the square brackets from the string
        match Hash.get(&variableName) { // hashmap lookup for the variable name inside the square brackets
            Some(S) => fixed = joined.replace(&variableReplacement, S), // set dummy string fixed to join modified with the variable value
            None => (), 
        }
    } 
    
    println!("{}", &fixed); //output the final string
}

fn CreateHashMap() -> HashMap<String, fn(&[&str], &mut HashMap<String, String>)> { //create the hash map for instruction to function saving
    let TokenHashMap: HashMap<String, fn(&[&str], &mut HashMap<String, String>)> = HashMap::from([
        ("remember".to_string(), remember as fn(&[&str], &mut HashMap<String, String>)),
        ("say".to_string(), say as fn (&[&str], &mut HashMap<String, String>)),
    ]);

    return TokenHashMap;
}


fn main() {
    let args: Vec<String> = std::env::args().collect();
    if args.len() == 1 { std::process::exit(1); } //make sure user passed some file 

    let sourceCode = fs::read_to_string(&args[1]).expect("Could not read file"); // read the file into a string

    let TokenHashMap = CreateHashMap(); // create the hash map 
    let mut VariableHashMap: HashMap<String, String> = HashMap::new();


    let clean = sourceCode.replace("\n", ""); // purge new lines
    let splitCode = clean.split(";"); // split the code by ;

    for line in splitCode { // loop through each line in the source code
        if line.len() == 0 { continue; } //if the line is empty then just continue
        if line.starts_with("//") { continue; } // LINE ACCOUNTS FOR COMMENTS

        let mut words = line.split(" "); // split the code by spaces
        
        let Some(S) = words.nth(0) else { return () }; // little rust magic, just getting the &str in S, None must be handled which is the reason for else return ()

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
