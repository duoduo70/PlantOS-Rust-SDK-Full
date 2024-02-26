#[no_mangle]
pub extern "C" fn start(_argc: i32, _argv: *const *const u8) -> i32 {
    let temp = unsafe { std::ffi::CStr::from_ptr(*_argv.wrapping_add(0) as *const i8) };
    println!("hello, {}!", temp.to_str().unwrap());
    0
}