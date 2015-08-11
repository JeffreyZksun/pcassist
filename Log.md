List the open source log libraries.

  * [boost log](http://boost-log.sourceforge.net/libs/log/doc/html/index.html) (C++)



  * [log4cpp](log4cpp.md) (C++)

  * [log4cplus](log4cplus.md) (C++)

  * [log4cx](log4cx.md) (C++)

  * [NLog](http://nlog-project.org/) (.Net, Silverlight and Windows Phone)
    * Files – single file or multiple, with automatic file naming and archival
    * Event Log – local or remote
    * Database – store your logs in databases supported by .NET
    * Network – using TCP, UDP, SOAP, MSMQ protocols
    * Command-line console – including color coding of messages
    * E-mail – you can receive emails whenever application errors occur
    * ASP.NET trace
> > … and many more


  * [Log4Net](http://logging.apache.org/log4net/index.html) (.Net)
    * log4net.Appender.AdoNetAppender 	Writes logging events to a database using either prepared statements or stored procedures.
    * log4net.Appender.AnsiColorTerminalAppender 	Writes color highlighted logging events to a an ANSI terminal window.
    * log4net.Appender.AspNetTraceAppender 	Writes logging events to the ASP trace context. These can then be rendered at the end of the ASP page or on the ASP trace page.
    * log4net.Appender.ColoredConsoleAppender 	Writes color highlighted logging events to the application's Windows Console.
    * log4net.Appender.ConsoleAppender 	Writes logging events to the application's Console. The events may go to either the standard our stream or the standard error stream.
    * log4net.Appender.DebugAppender 	Writes logging events to the .NET system.
    * log4net.Appender.EventLogAppender 	Writes logging events to the Windows Event Log.
    * log4net.Appender.FileAppender 	Writes logging events to a file in the file system.
    * log4net.Appender.LocalSyslogAppender 	Writes logging events to the local syslog service (UNIX only).
    * log4net.Appender.MemoryAppender 	Stores logging events in an in memory buffer.
    * log4net.Appender.NetSendAppender 	Writes logging events to the Windows Messenger service. These messages are displayed in a dialog on a users terminal.
    * log4net.Appender.OutputDebugStringAppender 	Writes logging events to the debugger. If the application has no debugger, the system debugger displays the string. If the application has no debugger and the system debugger is not active, the message is ignored.
    * log4net.Appender.RemoteSyslogAppender 	Writes logging events to a remote syslog service using UDP networking.
    * log4net.Appender.RemotingAppender 	Writes logging events to a remoting sink using .NET remoting.
    * log4net.Appender.RollingFileAppender 	Writes logging events to a file in the file system. The RollingFileAppender can be configured to log to multiple files based upon date or file size constraints.
    * log4net.Appender.SmtpAppender 	Sends logging events to an email address.
    * log4net.Appender.SmtpPickupDirAppender 	Sends logging events to an email address but writes the emails to a configurable directory rather than sending them directly via SMTP.
    * log4net.Appender.TelnetAppender 	Clients connect via Telnet to receive logging events.
    * log4net.Appender.TraceAppender 	Writes logging events to the .NET trace system.
    * log4net.Appender.UdpAppender 	Sends logging events as connectionless UDP datagrams to a remote host or a multicast group using a UdpClient.


  * Reference
  1. Disscussion regarding NLog vs Log4Net. http://stackoverflow.com/questions/710863/log4net-vs-nlog