How to use it ?

	1.You just need to download the project and compile it successfully for the whole solution.

	2.You can add your personal tool under the Common directory as new static lib projects.

	3.You should add your plugin interface to the Interface project and then add your own plugin project.

	4.You can export your plugins like we do for our core plugins. 

	5.You can use a plugin by using PluginPtr<Interface> wherever you need it.

Note: 

	There are some base tool for you such as String,Bool,Int,Double,Array<T>,Directory,File,Utf8,Ansi,Unicode,
	
	SerialPort,Usb,Player,DllLoader,ModuleLoader,EventHandler<T>,DateTime,Json,Ini,Log,Socket,SocketClient,
	
	SocketServer,SqlDatabase,Mutex,MutexLocker,Semaphone,Event,ThreadPool,Timer,Counter,Delay,etc.
