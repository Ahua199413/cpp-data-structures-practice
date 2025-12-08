# 根 Makefile (cpp-data-structures-practice/Makefile)

# 找出所有包含 Makefile 的子目錄
SUBDIRS := $(shell find . -maxdepth 1 -mindepth 1 -type d -name "??_*")

# 預設目標：遍歷所有子目錄並呼叫 'make' (編譯)
all:
	@for dir in $(SUBDIRS); do \
		echo ">>> Making in $$dir"; \
		$(MAKE) -C $$dir || exit 1; \
	done
# 清理目標：遍歷所有子目錄並呼叫 'make clean' (清理)
clean:
	@for dir in $(SUBDIRS); do \
		echo ">>> Cleaning in $$dir"; \
		$(MAKE) -C $$dir clean; \
	done