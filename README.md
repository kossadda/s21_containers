# s21_containers

Implementation of the s21_containers.h library.

The English version of the README can be found in the repository.

## Contents
1. [Project description](#project-description)
2. [Building project](#building-project)
3. [Team](#team)
4. [Feedback](#feedback)

<br>

## [Project description](#s21_containers)

This project implements a library that implements the main standard C++ container classes: list, map, queue, set, stack, vector, array, multiset. The tree container is implemented, which is an implementation of the red-black tree, on which the set, map, multiset containers are based. The implementations provide a set of standard methods and attributes for working with elements, checking if the container is full and iterating. 

Each type of container provides the following methods to the user:

- standard constructors (default constructor, copy constructor, move constructor, constructor with initialisation list, see materials);

- methods for accessing container elements (e.g., accessing an element with index i);

- methods of checking whether the container is full (e.g., the number of elements in the container, checking whether the container is empty);

- methods for modifying the container (deleting and adding new elements, cleaning the container);

- methods for working with the container iterator.

Iterators provide access to the elements of a container. For each container, the specific type of iterator will be different. This is due to the different kind of organisation of object sets in container classes, as well as the actual implementation of the container. Iterators are implemented in such a way that they work in a similar way to a pointer to a C array element. It is this approach through the use of iterators that allows any container to be interacted with in the same way. Containers provide iterators through the begin() and end() methods that point to the first and the next-to-last elements of the container, respectively.

## [Building project](#s21_containers)

The following main targets for working with the project have been added to the Makefile:

| #  | Target             | Target description                                                           |
|----| ------------------ | ---------------------------------------------------------------------------- |
| 1  | `all`              | Builds the project and generates project documentation.                      |
| 2  | `test`             | Performs module testing.                                                     |
| 3  | `dvi`              | Generates documentation in `html` and `manual` format for the functionality. |
| 4  | `clean`            | Cleans the repository of generated files.                                    |
| 5  | `rebuild`          | Rebuilds the project.                                                        |
| 6  | `clang_check`      | Testing modules for compliance with `Google style`.                          |
| 7  | `valgrind`         | Testing modules for working with memory using `Valgrind`.                    |

## [Team](#s21_containers)

- [@kossadda](https://github.com/kossadda) - implementation of map, set, multiset, vector containers.
- [@emmonbea](https://github.com/emmonbear) - implementation of list, stack, queue, array containers.

<br>

## [Feedback](#s21_containers)

If you have any questions regarding the features or other aspects of the project that interest you, please contact <br>

|          |                       |
| ---------| --------------------- |
| mail     | gabilov1997@gmail.com |
| telegram | @kossadda             |
| vk       | vk.com/kossadda       |

Thank you for your attention. I hope you enjoy this project and find it useful.

<br>

[К оглавлению](#s21_containers)