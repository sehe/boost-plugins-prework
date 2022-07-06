# boost-plugins-prework

See related SO post https://stackoverflow.com/a/72876823/85371

-----

Shared pointer is the problem. The `bind<>` template argument cannot be a pointer or reference type

> There's some information about why pointers are disallowed in `bind<>`: https://github.com/boost-ext/di/issues/317

I figured out a working way to bind the dependency:

```c++
const auto injector =
    di::make_injector(di::bind<ioperation>().to(
        [=, &use_sum](const auto& injector) -> op_ptr
        {
            return use_sum
                ? sum_creator()
                : dot_product_creator(sum_creator());
        }) //
    );
```

> Note that capturing the factory functions by value keeps the DLL around as long as the injector exists. This is safer than capturing by reference.
> Capturing the `use_sum` by reference highlights that the injector is dynamic. If that's not required, then I'd replace the whole injector with:
> 
> ```c++
> const auto injector = di::make_injector(di::bind<ioperation>().to(
>     use_sum ? sum_creator() : dot_product_creator(sum_creator())) //
> );
> ```

## Output

Using `compile_n_run.sh`:

    + ./cleanup.sh
    removed 'application_main'
    removed 'libdot_product.so'
    removed 'libsum.so'
    => cleaned up!
    + echo '=> Compiling now...'
    => Compiling now...
    + CPPFLAGS='-std=c++14 -fPIC -I /home/sehe/custom/boost-di/include/'
    + LDFLAGS=
    + g++ -std=c++14 -fPIC -I /home/sehe/custom/boost-di/include/ sum.cpp -shared -o libsum.so
    + g++ -std=c++14 -fPIC -I /home/sehe/custom/boost-di/include/ dot_product.cpp -shared -o libdot_product.so
    + LDFLAGS=' -lboost_filesystem -lboost_system -ldl'
    + g++ -std=c++14 -fPIC -I /home/sehe/custom/boost-di/include/ application_main.cpp -o application_main -lboost_filesystem -lboost_system -ldl
    + g++ -std=c++14 -fPIC -I /home/sehe/custom/boost-di/include/ application_di.cpp -o application_di -lboost_filesystem -lboost_system -ldl
    + ./application_main .
    [sum_constructor]
    [dot_product_constructor]
    [sum_constructor]
    [sum_constructor]
    [dot_product_constructor]
    
    Plugin Name: sum
    calculate(1, 2): 3
    
    Plugin Name: dot_product
    calculate(1, 2): 5
    [~dot_product_destructor]
    [~sum_destructor]
    [~sum_destructor]
    [~dot_product_destructor]
    [~sum_destructor]
    + ./application_di . use_sum
    [sum_constructor]
    name: sum
    [~sum_destructor]
    + ./application_di .
    [sum_constructor]
    [dot_product_constructor]
    name: dot_product
    [~dot_product_destructor]
    [~sum_destructor]

Or more live:[![enter image description here][1]][1]


  [1]: https://i.stack.imgur.com/RHpT7.gif

