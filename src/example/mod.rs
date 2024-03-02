macro_rules! test {
    ($fnname:expr) => {
        println!("--- test: {}", stringify!($fnname));
        $fnname();
        println!("--- test end");
    };
}
pub fn call_examples() {
    test!(print_something);
}

fn print_something() {
    println!("hello, rust!")
}