## 这是什么
这是一个可以直接使用 Rust 标准库开发 PlantOS 软件的 SDK 。

有一个[仅使用核心库的版本](https://github.com/duoduo70/PlantOS-Rust-SDK-Compact)。
## 如何使用
目前，仅可以使用 Linux 构建本项目。确保你已经安装了 Nightly Rust 、GNU/Make 、MUtils 、QEMU、GCC。

使用命令 `make` 即可直接构建示例程序。如果你要删除示例程序，可以直接删除 `src/example` 文件夹，并删除 `src/lib.rs` 中的相关代码。

开发流程应该是：如果有可以不改动转译层而使用的 API ，可以直接调用，如果没有，该存储库附带了一份转译层代码，应该修改转译层然后将修改后的转译层合并至[本仓库](https://github.com/duoduo70/PlantOS-Rust-SDK-Full)。
### 提示
目前，很多功能无法正常使用，例如 Rust 的内置单元测试。

如果你的开发环境能正常启动，就不要乱升级任何依赖，尤其是 ArchLinux 上的 Qemu ，因为它经常出问题并且降级回去会非常困难。

如果你直接通过 `make` 命令启动，它会包含 PRTL (PlantOS Rust Translation Layer，PlantOS Rust 转译层) 的调试输出，你可以使用 `make build` 来构建不带调试输出的版本。

使用 Rust 编写的程序的体积会比使用 C 编写大很多，但你可以通过按需增加 lib 来让程序减小很多。在确实需要的情况下，可以动态编译依赖库（这可能需要）
## 原理
我们通过转译层来伪装 PlantOS 为 Linux（默认）或其它操作系统（目前的转译层仅针对 Linux 开发）。

对 Linux 的 系统调用 (syscall) 会被转译成对 PlantOS 的 系统调用。

我们编写的程序会被编译为一个包含 `stdlib` 的静态链接库，它会和 libc 库，系统库，转译层库一起被链接成最终的程序。

它尽可能多的剔除了无用调用，并且 `stdlib` 是动态编译的，所以并不需要转译所有系统调用就可以正常编写或移植程序。
## 关于 boot.c
对于示例程序，主函数为 `start` ，它通过 `src/boot.c` 来引导——这意味着你可以通过修改 `boot.c` 来在 Rust 主函数被调用之前或之后做一些工作。事实上，引导函数可以增强架构的健壮性，防止在内核未来的开发中因为 libc 的更改而出现 Bug （避免让系统直接引导 Rust 程序，这一举措和 PRTL 属于一个层级）。另一方面，你可以有多个 Rust 主函数按顺序执行，这可能会让你能够方便的构建测试。
## 贡献说明
这是一项艰巨的工作，因为 Linux API 十分复杂，如果你愿意为其贡献代码，请发送 Issue 、PR 、或使用 [Email](mailto:anling@tuta.io) 联系我。