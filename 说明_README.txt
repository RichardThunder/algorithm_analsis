****************************************************************************************

            
                           本EFI支持10.13.6 - 10.15.x


****************************************************************************************

1、8代处理器需要设置BIOS高级模式，否则无法安装10.15.x，请认真看设置教程

   https://github.com/xiaoMGitHub/LEGION_Y7000Series_Hackintosh/blob/master/BIOS_Setup_Instructions.md

2、替换EFI，成功进入MacOS后，打开终端执行下面的命令（必须执行，否则会烧主板）

   sudo sh -c "$(curl -fsSL https://gitee.com/xiaoMGit/Y7000Series_Hackintosh_Fix/raw/master/Script/Optimize.sh)"

3、小键盘相关设置
  0）已经执行了上面的步骤
  1）打开终端执行 open /usr/local/bin/
  2）打开 系统偏好设置 > 安全性与隐私 > 隐私 > 辅助功能
  3）将 setleds 添加到辅助功能

4、屏蔽三星PM981/PM981a
  
  将 hotpatch/SSDT-DNVMe.aml 添加到 EFI/CLOVER/ACPI/patched



   