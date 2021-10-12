# ESP32 Prototyping Library

The library provides a few easy to use functionalities which allow to

# Modules
## Named Channels
The goal of this is to be create a public subscribe message service inside the application.
This enables the possibility to transfer information between source and sink, without that they know each other directly.
The channels need to be created in the beginning of the program. As soon es they are registered application parts
can observe them.