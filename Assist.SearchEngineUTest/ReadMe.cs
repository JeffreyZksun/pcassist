using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using NUnit.Framework;

// Use NUnit 2.6.0.11089  as the unit test framework.
// Download it from http://www.nunit.org/?p=download

// How to consume this framework.
// 0. Create a .net class library project.
// 1. Add reference to nunit framework.
// 2. Add using NUnit.Framework;
// 3. Add attribute TestFixture to the class.
// 4. Add attribute Test to the function.
// 5. Use Assert.AreEqual to test the value.
// 6. Compile the project
// 7. Open NUnit.exe In File | Open to open the dll created in the previous step. 
// 8. Click Run to run the result.
// 
namespace Assist.SearchEngineUTest
{
    [TestFixture]
    public class ReadMe
    {
        [Test]
        public void DummyTestFunction()
        {
            Assert.AreEqual("dummy", "dummy");
        }

    }
}
