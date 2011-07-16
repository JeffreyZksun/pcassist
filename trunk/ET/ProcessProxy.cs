using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using System.IO;
using System.Threading;

namespace ET
{
    class ProcessProxy
    {
        public ProcessProxy(String exeFullName, String argument
            , String workingDir)
        {
            mExeFullName = exeFullName;
            mArgument = argument;
            mWorkingDir = workingDir;
        }

        private String mExeFullName = "";
        private String mArgument = "";
        private String mWorkingDir = "";

        public event DataReceivedEventHandler ErrorDataReceived;
        public event DataReceivedEventHandler OutputDataReceived;

        public bool StartProcess()
        {
            Thread thread = new Thread(new ThreadStart(ThreadEntry));
            thread.IsBackground = true; // So that a failed connection attempt
            // wont prevent the process from terminating while it does the long timeout
            thread.Start();

            return true;
        }

        private void ThreadEntry()
        {
            ExecuteProcess(mExeFullName, mArgument, mWorkingDir);
        }

        private bool ExecuteProcess(String exeFullName, String argument
            , String workingDir)
        {
            Process myProcess = new Process();
            // The program or filename you want to run
            // It can be a file such as "example.txt".
            // It can be a program such as "WINWORD.EXE".
            myProcess.StartInfo.FileName = exeFullName;

            // Stores the arguments, such as -flags or filename.
            myProcess.StartInfo.Arguments = argument;

            //
            myProcess.StartInfo.WorkingDirectory = workingDir;

            // Allows you to run a command line program silently.
            // It does not flash a console window.
            myProcess.StartInfo.CreateNoWindow = true;

            // true to use the shell when starting the process; 
            // otherwise, the process is created directly from the executable file. The default is true.
            // Set false. It does not flash a console window.
            myProcess.StartInfo.UseShellExecute = false;

            // Redirect the output stream of the child process.
            // There is a known defect in GNU make.
            // It will fail if the output redirect is used.
            // Read more in http://www.zeusedit.com/forum/viewtopic.php?t=38
            myProcess.StartInfo.RedirectStandardOutput = true;
            myProcess.StartInfo.RedirectStandardError = true; // We just need the error message.

            myProcess.OutputDataReceived += new DataReceivedEventHandler(myProcess_OutputDataReceived);
            myProcess.ErrorDataReceived += new DataReceivedEventHandler(myProcess_ErrorDataReceived);

            try
            {
                myProcess.Start();

                // Do not wait for the child process to exit before
                // reading to the end of its redirected stream.
                // Otherwise, it will result in dead lock.

                // We can't read both StandardOutput and StandardError with the synchronous way.
                // It will result in dead lock
                // Refer to http://msdn.microsoft.com/en-us/library/system.diagnostics.process.standardoutput.aspx
                myProcess.BeginOutputReadLine(); // Start the asynchronous read of the output stream.

                // Read the standard output of the child process.
                //string outStr = myProcess.StandardOutput.ReadToEnd();

                myProcess.BeginErrorReadLine(); // Start the asynchronous read of the error stream.

                //result.ErrorMessage = myProcess.StandardError.ReadToEnd();

                myProcess.WaitForExit(); // Need we set the time limit?

                if (myProcess.ExitCode == 0)
                    return true;
                else
                {
                    return false;
                }

                myProcess.Close();
            }
            catch (System.Exception)
            {
                return false;
            }
        }

        void myProcess_ErrorDataReceived(object sender, DataReceivedEventArgs e)
        {
            if (this.ErrorDataReceived != null)
                this.ErrorDataReceived(sender, e);
        }

        void myProcess_OutputDataReceived(object sender, DataReceivedEventArgs e)
        {
            if (this.OutputDataReceived != null)
                this.OutputDataReceived(sender, e);
        }
    }
}
