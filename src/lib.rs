mod example;
#[no_mangle]
pub extern "C" fn start(_argc: i32, _argv: *const *const u8) -> i32 {
    example::call_examples();
    0
}