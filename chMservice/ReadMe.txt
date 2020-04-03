chMService 

////////////////
项目使用多字节字符集,非unioncode
项目的预定义属性需要修改为如下所示。
WIN32;NDEBUG;_WINDOWS;_CRT_NONSTDC_NO_DEPRECATE;_CRT_SECURE_NO_WARNINGS;%(PreprocessorDefinitions)


实现了:
1)install
2)uninstall

todo
具体业务逻辑。检测授权文件是否存在，检测授权日期，是否已经过期。