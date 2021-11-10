#include "CppUnitTest.h"
#include "C:\Users\Коля\Desktop\Laba\GitHub\Labs_153504_Klimkovich\5 laba\1\1.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{
	TEST_CLASS(Test)
	{
	public:
		
		TEST_METHOD(Test_1)
		{
			Assert::IsTrue(main() == 3635);
		}
	};
}
