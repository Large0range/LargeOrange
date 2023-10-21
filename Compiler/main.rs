#![allow(non_snake_case)]

mod keywordCallbacks;

use std::fs;
use std::collections::HashMap;


fn remember(args: &[&str], Hash: &mut HashMap<String, String>) {
    Hash.insert(args[0].to_string(), args[1].to_string());
}

fn say(args: &[&str], Hash: &mut HashMap<String, String>) {
    let joined = args.join(" ");
    println!("{}", &joined);
}

fn CreateHashMap() -> HashMap<String, fn(&[&str], &mut HashMap<String, String>)> {
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


    let clean = sourceCode.replace("\n", "");
    let splitCode = clean.split(";"); // split the code by ;

    for line in splitCode { // loop through each line in the source code
        let mut words = line.split(" "); // split the code by spaces
        
        let Some(S) = words.nth(0) else { return () }; // little rust magic, just getting the &str in S, None must be handled which is the reason for else return ()

        match TokenHashMap.get(&S.to_string()) {  //match the first word to a keyword in the hashmap
            Some(t) => {
                            let instructionArguments: Vec<&str> = (&mut words).skip(0).collect();
                            let x = &mut VariableHashMap;                        
                            t(&instructionArguments, x);
                        },
            None => panic!("Unknown instruction, {}", &S),
        }
    }
}
