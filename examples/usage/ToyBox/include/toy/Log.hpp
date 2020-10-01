
#include <memory>
#include <string>
#include <toy/Log.hpp>
#include <toy/Utf.hpp>
#include <toy/io/Writer.hpp>

// Change output target of log system.
static void ChangeOutputDevice(std::string outputFileName)
{
	auto writer = std::make_shared<toy::io::Writer<>>(outputFileName);

	toy::log::PushDevice( [writer](const char* str){writer->printf(str);},
	                      [writer](const wchar_t* str){writer->printf(toy::utf::WCharToUTF8(str).c_str());});
}

int main()
{
	// Just like std::printf
	toy::Log("%d hours a day\n",24);

	// Just like std::cout
	toy::Logger<<24<<" hours a day"<<toy::NewLine;

	// After this step. All message will be output to a text file(UTF-8).
	ChangeOutputDevice("note.txt");

	toy::Logger<<"Say something"<<toy::NewLine;

	// After this step. All message will be output to default device.
	toy::log::BackDefaultDevice();
}
