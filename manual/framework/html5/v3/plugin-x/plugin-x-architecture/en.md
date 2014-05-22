#Plugin-x Architecture

##What is Plugin-x
Plugin-x is a protocal of third-party SDKs used in games. We can easily use third-party SDK with plugin-x, and no longer need to write JNI code or javascript binding code. Right now there is analytics, IAP, ads and social SDKs integrated in plugin-x. And you can integrate any SDK into plugin-x as you wish.

##plugin-x architecture

Because most third-party SDKs are written in Objective-C or Java, we have make some wrapper in C++ to use reflection easily, and abstract analytics protocal, IAP protocal, ads protocal and so on. To integrate a third-party SDK as a plugin, we only need to implement the interfaces of protocals. When we use a SDK in our game, we just load the  plugin, and invoke the interfaces of protocals.

The architecture of plugin-x is showing below:

![](res/plugin-x-architecture.jpg)

The process of loading plugin, invoking interface, uploading plugin is showing below:

![](res/plugin-x-sequence-chart.jpg)