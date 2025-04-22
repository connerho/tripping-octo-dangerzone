fn get_divisors(str: String) -> Vec<String> {
    let mut result: Vec<String> = Vec::new();
    let quitting_size: usize = str.len() / 2;
    let mut current_idx = 0;

    while current_idx < quitting_size {
        let substr: String = (&str[0..current_idx+1]).to_string();
        let mut sub_idx = current_idx + 1;
        let mut made_it = true;

        while (sub_idx + current_idx + 1) <= str.len()  {
            if substr != &str[sub_idx..(sub_idx + current_idx + 1)] {
                made_it = false;
                break;
            }
            sub_idx += current_idx + 1;
        }

        if sub_idx < str.len() {
            made_it = false;
        }

        if made_it {
            result.push(substr);
        }
        current_idx += 1;
    }

    // Should always push the entire string to the vector
    result.push(str);
    return result;
}

fn gcd_of_strings(str1: String, str2: String) -> String {
    let mut result: String = String::new();

    let vec1 = get_divisors(str1);
    let vec2 = get_divisors(str2);

    for my_str1 in &vec1 {
        for my_str2 in &vec2 {
            if my_str1 == my_str2 {
                if my_str1.len() > result.len() {
                    result = my_str1.to_string();
                }
            }
        }
    }

    return result;
}

fn main() {
    let str1: String = String::from("ABC");
    let str2: String = String::from("ABCABC");
    let result = gcd_of_strings(str1, str2);
    println!("{result}");
}
