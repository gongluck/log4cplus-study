// log4cplus-study.cpp: 定义控制台应用程序的入口点。
//

///参考https://my.oschina.net/lovecxx/blog/185951

#include "stdafx.h"

#include <iostream>
#include <iomanip>

#include <log4cplus/logger.h>
#include <log4cplus/layout.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/ndc.h>
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>

using namespace log4cplus;
using namespace log4cplus::helpers;

#ifdef _DEBUG
#pragma comment(lib, "../log4cplusD.lib")
#else
#pragma comment(lib, "../log4cplus.lib")
#endif

//标准使用
void log1()
{
	/* step 1: Instantiate an appender object */
	SharedObjectPtr<Appender> _append(new ConsoleAppender());
	_append->setName("append for test");

	/* step 2: Instantiate a layout object */
	std::string pattern = "%d{%m/%d/%y  %H:%M:%S}  - %m [%l]%n";
	std::auto_ptr<Layout> _layout(new PatternLayout(pattern));

	/* step 3: Attach the layout object to the appender */
	_append->setLayout(_layout);

	/* step 4:  Instantiate a logger object */
	Logger _logger = Logger::getInstance("log1");

	/* step 5: Attach the appender object to the  logger  */
	_logger.addAppender(_append);

	/* step 6: Set a priority for the logger  */
	_logger.setLogLevel(ALL_LOG_LEVEL);

	/* log activity */
	LOG4CPLUS_DEBUG(_logger, "This is the  FIRST log message...");
	LOG4CPLUS_WARN(_logger, "This is the  SECOND log message...");
}

//简洁使用
void log2()
{
	/* step 1: Instantiate an appender object */
	SharedAppenderPtr _append(new ConsoleAppender());
	_append->setName("append  test");

	/* step 4: Instantiate a logger object */
	Logger _logger = Logger::getInstance("log2");

	/* step 5: Attach the appender object to the  logger  */
	_logger.addAppender(_append);

	/* log activity */
	LOG4CPLUS_DEBUG(_logger, "This is the  FIRST log message...");
	LOG4CPLUS_WARN(_logger, "This is the  SECOND log message...");
}

//输出日志到控制台
void log3()
{
	/* step 1 : Instantiate an appender object */
	SharedAppenderPtr _append(new  ConsoleAppender());
	_append->setName("append test");

	/* step 4 : Instantiate a logger object */
	Logger _logger = Logger::getInstance("log3");

	/* step 5 : Attach the appender object to the logger */
	_logger.addAppender(_append);

	/* logactivity */
	LOG4CPLUS_TRACE(_logger, "This is" << "just a t" << "est." << std::endl);
	LOG4CPLUS_DEBUG(_logger, "This is a bool:" << true);
	LOG4CPLUS_INFO(_logger, "This is a char:" << 'x');
	LOG4CPLUS_WARN(_logger, "This is a int:" << 1000);
	LOG4CPLUS_ERROR(_logger, "This is a long(hex):" << std::hex << 100000000);
	LOG4CPLUS_FATAL(_logger, "This is a double:" << std::setprecision(15) << 1.2345234234);
}

//输出日志到文件
void log4()
{
	/* step 1 : Instantiate an appender object */
	SharedAppenderPtr _append(new FileAppender("log4"));
	_append->setName("filelog test");

	/* step 4 : Instantiate a logger object */
	Logger _logger = Logger::getInstance("log4");

	/* step 5 : Attach the appender object to the logger */
	_logger.addAppender(_append);

	/* logactivity */
	for (int i = 0; i < 5; ++i) 
	{
		LOG4CPLUS_DEBUG(_logger, "Entering loop# " << i << " Endline#");
	}
}

//使用loglog输出日志
void printMsgs(void)
{
	std::cout << "Entering  printMsgs()..." << std::endl;
	LogLog::getLogLog()->debug("This is a  Debug statement...");
	LogLog::getLogLog()->warn("This is a  Warning...");
	LogLog::getLogLog()->error("This is a  Error...");
	std::cout << "Exiting  printMsgs()..." << std::endl << std::endl;

}
void log5()
{
	printMsgs();
	std::cout << "Turning on  debug..." << std::endl;
	LogLog::getLogLog()->setInternalDebugging(true);
	printMsgs();
	std::cout << "Turning on  quiet mode..." << std::endl;
	LogLog::getLogLog()->setQuietMode(true);
	printMsgs();
}

//SimpleLayout
void log6()
{
	/* step 1:  Instantiate an appender object */
	SharedAppenderPtr  _append(new ConsoleAppender());
	_append->setName("append for  test");

	/* step 2:  Instantiate a layout object */
	std::auto_ptr<Layout>  _layout(new  log4cplus::SimpleLayout());

	/* step 3: Attach  the layout object to the appender */
	_append->setLayout(_layout);

	/* step 4:  Instantiate a logger object */
	Logger _logger = Logger::getInstance("log6");

	/* step 5: Attach  the appender object to the logger  */
	_logger.addAppender(_append);

	/* log activity */
	LOG4CPLUS_DEBUG(_logger, "This  is the simple formatted log message...");
}

//PatternLayout
void log7()
{
	/* step 1:  Instantiate an appender object */
	SharedAppenderPtr _append(new  ConsoleAppender());
	_append->setName("append for  test");

	/* step 2:  Instantiate a layout object */
	std::string  pattern = "%d{%m/%d/%y  %H:%M:%S}  - %m [%l]%n";
	/*
	PatterLayout支持的转换标识符主要包括：
	（1）"%%"，转义为%, 即，std::string pattern = "%%" 时输出"%"。
	（2）"%c"，输出logger名称，比如std::string pattern ="%c" 时输出: "test_logger.subtest"，也可以控制logger名称的显示层次，比如"%c{1}"时输出"test_logger"，其中数字表示层次。
	（3）"%D"，显示本地时间，当std::string pattern ="%D" 时输出:"2004-10-16 18:55:45"，%d显示标准时间，所以当std::string pattern ="%d" 时输出"2004-10-16 10:55:45" （因为北京时间位于东8区，差8个小时）。
	可以通过%d{...}定义更详细的显示格式，比如%d{%H:%M:%s}表示要显示小时:分钟：秒。大括号中可显示的预定义标识符如下：
	%a -- 表示礼拜几，英文缩写形式，比如"Fri"
	%A -- 表示礼拜几，比如"Friday"
	%b -- 表示几月份，英文缩写形式，比如"Oct"
	%B -- 表示几月份，"October"
	%c -- 标准的日期＋时间格式，如 "Sat Oct 16 18:56:19 2004"
	%d -- 表示今天是这个月的几号(1-31)"16"
	%H -- 表示当前时刻是几时(0-23)，如 "18"
	%I -- 表示当前时刻是几时(1-12)，如 "6"
	%j -- 表示今天是哪一天(1-366)，如 "290"
	%m -- 表示本月是哪一月(1-12)，如 "10"
	%M -- 表示当前时刻是哪一分钟(0-59)，如 "59"
	%p -- 表示现在是上午还是下午， AM or PM
	%q -- 表示当前时刻中毫秒部分(0-999)，如 "237"
	%Q -- 表示当前时刻中带小数的毫秒部分(0-999.999)，如 "430.732"
	%S -- 表示当前时刻的多少秒(0-59)，如 "32"
	%U -- 表示本周是今年的第几个礼拜，以周日为第一天开始计算(0-53)，如 "41"
	%w -- 表示礼拜几，(0-6, 礼拜天为0)，如 "6"
	%W -- 表示本周是今年的第几个礼拜，以周一为第一天开始计算(0-53)，如 "41"
	%x -- 标准的日期格式，如 "10/16/04"
	%X -- 标准的时间格式，如 "19:02:34"
	%y -- 两位数的年份(0-99)，如 "04"
	%Y -- 四位数的年份，如 "2004"
	%Z -- 时区名，比如 "GMT"
	（4）"%F"，输出当前记录器所在的文件名称，比如std::string pattern ="%F" 时输出: "main.cpp"。
	（5）"%L"，输出当前记录器所在的文件行号，比如std::string pattern ="%L" 时输出: "51"
	（6）"%l"，输出当前记录器所在的文件名称和行号，比如std::string pattern ="%l" 时输出"main.cpp:51"。
	（7）"%m"，输出原始信息，比如std::string pattern ="%m" 时输出: "teststr"，即上述代码中LOG4CPLUS_DEBUG的第二个参数，这种实现机制可以确保原始信息被嵌入到带格式的信息中。
	（8）"%n"，换行符，没什么好解释的。
	（9）"%p"，输出LogLevel，比如std::string pattern ="%p" 时输出: "DEBUG"。
	（10）"%t"，输出记录器所在的线程ID，比如std::string pattern ="%t" 时输出: "1075298944"。
	（11）"%x"，嵌套诊断上下文NDC (nested diagnostic context) 输出，从堆栈中弹出上下文信息，NDC可以用对不同源的log信息（同时地）交叉输出进行区分，关于NDC方面的详细介绍会在下文中提到。
	（12）格式对齐，比如std::string pattern ="%-10m"时表示左对齐，宽度是10，此时会输出"teststr   "，当然其它的控制字符也可以相同的方式来使用，比如"%-12d"，"%-5p"等等。
	*/
	std::auto_ptr<Layout>  _layout(new  PatternLayout(pattern));

	/* step 3: Attach  the layout object to the appender */
	_append->setLayout(_layout);

	/* step 4:  Instantiate a logger object */
	Logger _logger = Logger::getInstance("log7");

	/* step 5: Attach  the appender object to the logger  */
	_logger.addAppender(_append);

	/* log activity */
	LOG4CPLUS_DEBUG(_logger, "teststr");
}

//TTCCLayout
void log8()
{
	/*step1:Instantiateanappenderobject*/
	SharedAppenderPtr _append(new  ConsoleAppender());
	_append->setName("appendfortest");

	/* step 2 : Instantiate a layout object */
	std::auto_ptr<Layout> _layout(new TTCCLayout());

	/* step 3 : Attach the layout object to the appender */
	_append->setLayout(_layout);

	/* step 4 : Instantiate a logger object */
	Logger _logger = Logger::getInstance("log8");

	/* step 5 : Attach the appender object to thelogger */
	_logger.addAppender(_append);

	/* logactivity */
	LOG4CPLUS_DEBUG(_logger, "teststr");
}

//滚动存储文件RollingFileAppender
void log9()
{
#define LOOP_COUNT 200000
	SharedAppenderPtr  _append(new  RollingFileAppender("log9", 5 * 1024, 5));//log4cplus中隐含定义了文件的最小尺寸是200K，只有大于200K的设置才生效，<= 200k的设置都会被认为是200K
	_append->setName("file  test");
	_append->setLayout(std::auto_ptr<Layout>(new  TTCCLayout()));
	Logger _logger = Logger::getInstance("log9");
	_logger.addAppender(_append);
	
	for (int i = 0; i < LOOP_COUNT; ++i) 
	{
		LOG4CPLUS_DEBUG(_logger, "Entering  loop #" << i);
	}
}

//频率存储文件DailyRollingFileAppender
void log10()
{
#define LOOP_COUNT 200000
	SharedAppenderPtr  _append(new  DailyRollingFileAppender("log10", MINUTELY, true, 5));
	_append->setName("file  test");
	_append->setLayout(std::auto_ptr<Layout>(new  TTCCLayout()));
	Logger _logger = Logger::getInstance("log10");
	_logger.addAppender(_append);

	for (int i = 0; i < LOOP_COUNT; ++i) 
	{
		LOG4CPLUS_DEBUG(_logger, "Entering  loop #" << i);
	}
}

//(线程)嵌入诊断上下文NDC
void log11()
{
	/* step 1:  Instantiate an appender object */
	SharedAppenderPtr _append(new  ConsoleAppender());
	_append->setName("append for  test");

	/* step 2:  Instantiate a layout object */
	std::string  pattern = "NDC:[%x]  - %m %n";
	std::auto_ptr<Layout>  _layout(new  PatternLayout(pattern));

	/* step 3: Attach  the layout object to the appender */
	_append->setLayout(_layout);

	/* step 4:  Instantiate a logger object */
	Logger _logger = Logger::getInstance("log11");

	/* step 5: Attach  the appender object to the logger  */
	_logger.addAppender(_append);

	NDCContextCreator _first_ndc("ur ndc string");
	LOG4CPLUS_DEBUG(_logger, "this is a NDC test");
}

//日志的优先级和过滤
void log12()
{
	SharedAppenderPtr _append(new ConsoleAppender());
	_append->setName("test");

	Logger::getRoot().addAppender(_append);
	Logger root = Logger::getRoot();
	Logger test = Logger::getInstance("log12");
	Logger subTest = Logger::getInstance("log12.subtest");

	LogLevelManager& llm = getLogLevelManager();

	std::cout << std::endl << "Before  Setting, Default LogLevel" << std::endl;

	LOG4CPLUS_FATAL(root, "root: " << llm.toString(root.getChainedLogLevel()));
	LOG4CPLUS_FATAL(root, "test: " << llm.toString(test.getChainedLogLevel()));
	LOG4CPLUS_FATAL(root, "test.subtest:" << llm.toString(subTest.getChainedLogLevel()));

	std::cout << std::endl << "Setting  log12.subtest to WARN" << std::endl;
	subTest.setLogLevel(WARN_LOG_LEVEL);

	LOG4CPLUS_FATAL(root, "root: " << llm.toString(root.getChainedLogLevel()));
	LOG4CPLUS_FATAL(root, "test: " << llm.toString(test.getChainedLogLevel()));
	LOG4CPLUS_FATAL(root, "test.subtest:  " << llm.toString(subTest.getChainedLogLevel()));

	std::cout << std::endl << "Setting test  to TRACE" << std::endl;
	test.setLogLevel(TRACE_LOG_LEVEL);

	LOG4CPLUS_FATAL(root, "root: " << llm.toString(root.getChainedLogLevel()));
	LOG4CPLUS_FATAL(root, "test: " << llm.toString(test.getChainedLogLevel()));
	LOG4CPLUS_FATAL(root, "test.subtest:  " << llm.toString(subTest.getChainedLogLevel()));

	std::cout << std::endl << "Setting  test.subtest to NO_LEVEL" << std::endl;
	subTest.setLogLevel(NOT_SET_LOG_LEVEL);

	LOG4CPLUS_FATAL(root, "root: " << llm.toString(root.getChainedLogLevel()));
	LOG4CPLUS_FATAL(root, "test: " << llm.toString(test.getChainedLogLevel()));
	LOG4CPLUS_FATAL(root, "test.subtest:  " << llm.toString(subTest.getChainedLogLevel()) << '\n');

	std::cout << "create a logger test_bak,  named \"test_\", too. " << std::endl;
	Logger test_bak = Logger::getInstance("test");

	std::cout << "Setting test to INFO, so  test_bak also be set to INFO" << std::endl;
	test.setLogLevel(INFO_LOG_LEVEL);

	LOG4CPLUS_FATAL(root, "test: " << llm.toString(test.getChainedLogLevel()));
	LOG4CPLUS_FATAL(root, "test_bak:  " << llm.toString(test_bak.getChainedLogLevel()));
}

//使用脚本配置
void log13()
{
	//PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT("urconfig.properties"));
	ConfigureAndWatchThread("urconfig.properties");

	Logger logger = Logger::getInstance(LOG4CPLUS_TEXT("log13"));

	LOG4CPLUS_TRACE_METHOD(logger, LOG4CPLUS_TEXT("::printDebug()"));
	LOG4CPLUS_DEBUG(logger, "This is a DEBUG message");
	LOG4CPLUS_INFO(logger, "This is a INFO message");
	LOG4CPLUS_WARN(logger, "This is a WARN message");
	LOG4CPLUS_ERROR(logger, "This is a ERROR message");
	LOG4CPLUS_FATAL(logger, "This is a FATAL message");
}

int main()
{
	log1();
	log2();
	log3();
	log4();
	log5();
	log6();
	log7();
	log8();
	log9();
	log10();

	log11();
	log12();
	log13();

	system("pause");
	return 0;
}