cmake_minimum_required(VERSION 3.6)
project(Pandemic)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Board.cpp
        Board.h
        BuildResearchStation.cpp
        BuildResearchStation.h
        Card.cpp
        Card.h
        CardType.cpp
        CardType.h
        CharterFlight.cpp
        CharterFlight.h
        City.cpp
        City.h
        CityVertex.cpp
        CityVertex.h
        Deck.cpp
        Deck.h
        DirectFlight.cpp
        DirectFlight.h
        DiscoverCure.cpp
        DiscoverCure.h
        DiseaseColour.cpp
        DiseaseColour.h
        DriveOrFerry.cpp
        DriveOrFerry.h
        Edge.cpp
        Edge.h
        Game.cpp
        Game.h
        Graph.cpp
        Graph.h
        Main.cpp
        PawnColour.cpp
        PawnColour.h
        Player.cpp
        Player.h
        RoleCard.cpp
        RoleCard.h
        ShareKnowledge.cpp
        ShareKnowledge.h
        ShuttleFlight.cpp
        ShuttleFlight.h
        Strategy.h
        TreatDisease.cpp
        TreatDisease.h
        TurnTaker.h
        Util.cpp
        Util.h
        Vertex.cpp
        Vertex.h GameBuilder.cpp GameBuilder.h SaveLoadDirector.cpp SaveLoadDirector.h)

add_executable(Pandemic ${SOURCE_FILES})

set(Boost_INCLUDE_DIR /usr/local/Cellar/boost/1.63.0/include)
set(Boost_LIBRARY_DIR /usr/local/Cellar/boost/1.63.0/lib)
find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})