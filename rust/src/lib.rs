/// # 获取类型名(get type name)
/// ```
/// assert_eq!("rust::hello_world", rust::type_of(&rust::hello_world));
/// ```
pub fn type_of<T>(_: &T) -> String {
    format!("{}", std::any::type_name::<T>())
}

pub fn call<T>(f: &T)
where T : Fn()
{
    println!("Start {}", type_of(&f));
    f();
    println!("End {}", type_of(&f));
}
pub fn hello_world() {
    println!("hello world!");
}
