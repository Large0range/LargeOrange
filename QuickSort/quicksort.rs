fn main() {
    let mut array = vec![8, 2, 7, 1, 3, 4, 6, 9, 5]; 
    println!("{:?}", array);
        
    
    let end = array.len()-1;
    fuckin_sort::<i32>(&mut array, 0, end);
    println!("{:?}", array);
}

fn fuckin_sort<T: Clone + std::cmp::PartialOrd>(array: &mut Vec<T>, start: usize, end: usize) { // all usize must be valid index, for example for end if the array size is 9 don't pass fucking 9, pass 8
    if end <= start { return (); } // base case so function doesn't go on forever
    

    let pivot: T = array[end].clone(); // clone end element for pivot value
    let mut i = start; // set i to start value
    let mut j = start; // set j to start value
    let mut tmp: T; // set tmp variable to abstract value
    
    let mut unrealFlag: bool = true; // create a flag to only trigger once because usize is retarded
    while i <= end { // loop until i reaches the end of the array
        if array[i] <= pivot { // check if the value at i is less than or equal to the pivot value
            if unrealFlag { unrealFlag = false; } // if this is the first value in the array, trigger the unreal flag so that j doesn't increment like a loser
            else { j+=1; } // if it's not then bring j up to speed on current world events

            if i > j { // make sure i is greater than j because racial inequality
                tmp = array[j].clone(); // set tmp to a clone of the value at j for storage purposes
                array[j] = array[i].clone(); // set j equal to whatever the fuck is at i
                array[i] = tmp; // set i to whatever the fuck used to be at j
            } // go home get a beer 
        }
        i += 1; // move on and do it again
    }

    if j > 1 { sort::<T>(array, start, j-1); } // partition sort wrapped in an if statement again because usize is a wanker
    sort::<T>(array, j+1, end); // this is my favorite child
}
