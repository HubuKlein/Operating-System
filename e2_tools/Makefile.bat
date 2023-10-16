
# 默认动作

default :
	./make.exe img

# 镜像文件生成

helloos.bin : helloos.nas Makefile
	./nask.exe helloos.nas helloos.bin helloos.lst

helloos.img : helloos.bin Makefile
	./edimg.exe   imgin:./fdimg0at.tek \
		wbinimg src:helloos.bin len:512 from:0 to:0   imgout:helloos.img

# 其他指令

asm :
	./make.exe -r helloos.bin

img :
	./make.exe -r helloos.img

run :
	./make.exe img
	copy helloos.img ..\e2_tools\qemu\fdimage0.bin
	./make.exe -C ../e2_tools/qemu

install :
	./make.exe img
	./imgtol.com w a: helloos.img

clean :
	-del helloos.bin
	-del helloos.lst

src_only :
	./make.exe clean
	-del helloos.img
