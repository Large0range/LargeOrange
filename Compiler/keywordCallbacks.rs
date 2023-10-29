use std::collections::HashMap;

pub fn remember(args: &[&str], Hash: &mut HashMap<String, String>) { // function for the remember instruction
    Hash.insert(args[0].to_string(), args[1].to_string()); // insert variable name and value into hash map 
}


pub fn say(args: &[&str], _Hash: &mut HashMap<String, String>) { // function for telling the computer to output something
    let joined = args.join(" "); // join the following arguments passed to the say instruction
    
    
    println!("{}", joined); //output the final string
}

pub fn add(args: &[&str], Hash: &mut HashMap<String, String>) {
    let variableName = args[0]; // get the variable to store the output in 
    
    let int1 = args[1].parse::<i32>().unwrap(); // get the first number, parse and unwrap both
    let int2 = args[2].parse::<i32>().unwrap(); // get the second number

    Hash.insert(variableName.to_string(), (int1+int2).to_string());
}

pub fn sub(args: &[&str], Hash: &mut HashMap<String, String>) {
    let variableName = args[0]; // get the variable to store the output in 
    
    let int1 = args[1].parse::<i32>().unwrap(); // get the first number, parse and unwrap both
    let int2 = args[2].parse::<i32>().unwrap(); // get the second number


    Hash.insert(variableName.to_string(), (int1-int2).to_string());
}

pub fn mul(args: &[&str], Hash: &mut HashMap<String, String>) {
    let variableName = args[0]; // get the variable to store the output in 
    
    let int1 = args[1].parse::<i32>().unwrap(); // get the first number, parse and unwrap both
    let int2 = args[2].parse::<i32>().unwrap(); // get the second number


    Hash.insert(variableName.to_string(), (int1*int2).to_string());
}

pub fn div(args: &[&str], Hash: &mut HashMap<String, String>) {
    let variableName = args[0]; // get the variable to store the output in 
    
    let int1 = args[1].parse::<i32>().unwrap(); // get the first number, parse and unwrap both
    let int2 = args[2].parse::<i32>().unwrap(); // get the second number


    Hash.insert(variableName.to_string(), (int1/int2).to_string());    
}
