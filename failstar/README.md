FAIL* - FAult Injection Leveraged
=======================================

Current progress
----------------

### What's done

- FAIL* is now compilable with LLVM 4.0 (versions >=4.0 include AVR backend)
- fail-targets runs correctly with LLVM 4.0 and Bochs
- Import SimulAVR to FAIL* simulators
- Preparing Fail* with SimulAVR for being an external library


### What's to do

- Understand in detail and implement AVR Processor
- Implement Fail*-based dependencies for running SimulAVR in Fail*
- Compiling SimulAVR via FAIL* cmake environment
- Construct appropriate programs for AVR simulations
- fail-targets runs with SimulAVR


FAIL*
-----

### Building FAIL* with LLVM 4.0

Packages required (build on an Ubuntu 16.04)

    sudo apt-get install -y cmake texinfo binutils-dev libboost-regex-dev libboost-system-dev libboost-coroutine-dev libboost-regex-dev libboost-context-dev libboost-thread-dev protobuf-compiler libprotobuf-dev libiberty-dev libmysqlclient-dev doxygen libpcl1-dev libelf-dev libdwarf-dev libncursesw5-dev lib32ncurses5-dev libsdl-dev libsdl2-dev libsdl1.2-dev libfontconfig1-dev llvm-4.0 xorriso sshfs grub-pc-bin

AspectC++ required

    wget -P ~/bin/ http://aspectc.org:8080/job/Daily/lastSuccessfulBuild/artifact/aspectcpp-linux64-daily.tar.gz && tar -C ~/bin/ -xzf ~/bin/aspectcpp-linux64-daily.tar.gz && rm ~/bin/aspectcpp-linux64-daily.tar.gz
    echo 'export PATH=~/bin/aspectc++:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin' >> ~/.bashrc && source ~/.bashrc

Optional for some case

    sudo apt-get aptitude
    sudo aptitude install -y libgtk2.0-dev libwxgtk2.8-dev libwxbase2.8-dev python-numpy python-matplotlib

Clone FAIL* from SRA repository (SSH connection required)

    git clone ssh://git@scm.sra.uni-hannover.de/diffusion/68/avrstar.git <fail_dir_trace>

Build experiments in two separate directories for testing

    mkdir <fail_dir_experiment> && cp -r <fail_dir_trace> <fail_dir_experiment>
    mkdir <fail_dir_trace>/build && cd <fail_dir_trace>/build
    ../configurations/x86_pruning.sh generic-tracing
    make -j<n>
    mkdir <fail_dir_experiment>/build && cd <fail_dir_experiment>/build
    ../configurations/x86_pruning.sh generic-experiment
    make -j<n>

Copy binaries and bochs-experiment-script (`/usr/local/bin/` is an easy way)

    sudo cp <fail_dir_trace>/build/bin/{import-trace,prune-trace} /usr/local/bin/
    sudo cp <fail_dir_trace>/build/bin/fail-client /usr/local/bin/fail-x86-tracing
    sudo cp <fail_dir_experiment>/build/bin/generic-experiment-server /usr/local/bin/
    sudo cp <fail_dir_experiment>/build/bin/fail-client /usr/local/bin/generic-experiment-client
    sudo cp <fail_dir_experiment>/tools/bochs-experiment-runner/bochs-experiment-runner.py  /usr/local/bin/
    sudo chmod +x /usr/local/bin/bochs-experiment-runner.py

### Run demo experiment

see https://scm.sra.uni-hannover.de/diffusion/156/


### ...or run demo experiment with unmodified fail-targets

Clone fail-targets

    git clone https://github.com/danceos/fail-targets.git <fail-targets_dir>

The system-under test is built and traced with

    cd <fail-targets_dir>
    make
    make trace-main

The golden run is traced with:

    make import-main

The fault injection itself is separated into a server process and many
injection workers. Both can be started at once with:

    make server-main &
    make client-main

The results can be displayed on the console or with an browser-based
viewer. By default, port 5000 is exposed to the machine running the
docker instance.

    make result-main
    make resultbrowser


Mailing list
------------
The FAIL* developers, and some of its previous and current users, can be
contacted on the
[fail@lists.cs.tu-dortmund.de](mailto:fail@lists.cs.tu-dortmund.de)
mailing list
([subscribe!](https://postamt.cs.uni-dortmund.de/mailman/listinfo/fail)).

Publications about FAIL*
------------------------
Please cite the EDCC paper if you want to refer to FAIL*:

 - H. Schirmeier, M. Hoffmann, C. Dietrich, M. Lenz, D. Lohmann, and O.
   Spinczyk. FAIL*: An open and versatile fault-injection framework for the
   assessment of software-implemented hardware fault tolerance. In Proceedings
   of the 11th European Dependable Computing Conference (EDCC '15), pages
   245–255.  IEEE Computer Society Press, Sept. 2015.
   [PDF](http://www.danceos.org/publications/EDCC-2015-Schirmeier.pdf)

 - H. Schirmeier. Efficient Fault-Injection-based Assessment of
   Software-Implemented Hardware Fault Tolerance. Dissertation, Technische
   Universität Dortmund, July 2016.

 - H. Schirmeier, M. Hoffmann, R. Kapitza, D. Lohmann, and
   O. Spinczyk. FAIL*: Towards a versatile fault-injection experiment
   framework. In G. Mühl, J. Richling, and A. Herkersdorf, editors,
   25th International Conference on Architecture of Computing Systems
   (ARCS '12), Workshop Proceedings, volume 200 of Lecture Notes in
   Informatics, pages 201–210. German Society of Informatics,
   Mar. 2012.
   [PDF](http://danceos.org/publications/VERFE-2012-Schirmeier.pdf)

Selected publications using FAIL*
---------------------------------

- O. Pusz, D. Kiechle, C. Dietrich, D. Lohmann.  Program-Structure–Guided
  Approximation of Large Fault Spaces. In Proceedings of the 24th IEEE Pacific
  Rim International Symposium on Dependable Computing (PRDC '19). IEEE Computer
  Society Press, Dec. 2019.

- C. Borchert. Aspect-Oriented Technology for Dependable Operating Systems.
  Dissertation, Technische Universität Dortmund, May 2017.

- C. Borchert, H. Schirmeier, and O. Spinczyk. Generic soft-error detection and
  correction for concurrent data structures. IEEE Transactions on Dependable
  and Secure Computing, PP(99). IEEE Computer Society Press.  In preprint.

- H. Schirmeier. Efficient Fault-Injection-based Assessment of
  Software-Implemented Hardware Fault Tolerance. Dissertation, Technische
  Universität Dortmund, July 2016.

- M. Hoffmann. Konstruktive Zuverlässigkeit – Eine Methodik für zuverlässige
  Systemsoftware auf unzuverlässiger Hardware. Dissertation,
  Friedrich-Alexander-Universität Erlangen-Nürnberg, Apr. 2016.

- C. Borchert and O. Spinczyk. Hardening an L4 microkernel against soft errors
  by aspect-oriented programming and whole-program analysis. In Proceedings of
  the 8th Workshop on Programming Languages and Operating Systems (PLOS '15),
  pages 1–7, New York, NY, USA, Oct. 2015. ACM Press.

- T. Stumpf. How to Protect the Protector?  In Proceedings of the 45th Annual
  IEEE/IFIP International Conference on Dependable Systems and Networks (DSN '15),
  Student Forum. IEEE Computer Society Press, June 2015.

- C. Dietrich, M. Hoffmann, and D. Lohmann. Cross-kernel control-flow-graph
  analysis for event-driven real-time systems. In Proceedings of the 2015 ACM
  SIGPLAN/SIGBED Conference on Languages, Compilers and Tools for Embedded
  Systems (LCTES '15), New York, NY, USA, June 2015. ACM Press.

- H. Schirmeier, C. Borchert, and O. Spinczyk. Avoiding pitfalls in
  fault-injection based comparison of program susceptibility to soft errors. In
  Proceedings of the 45th IEEE/IFIP International Conference on Dependable
  Systems and Networks (DSN '15). IEEE Computer Society Press, June 2015.

- M. Hoffmann, F. Lukas, C. Dietrich, and D. Lohmann. dOSEK: The design and
  implementation of a dependability-oriented static embedded kernel. In
  Proceedings of the 21st IEEE Real-Time and Embedded Technology and
  Applications (RTAS '15), Los Alamitos, CA, USA, Apr. 2015. IEEE Computer
  Society Press.

- Christian Dietrich and Daniel Lohmann. The dataref versuchung. ACM Operating
  Systems Review, pages 1–10, 2015.

- M. Hoffmann, P. Ulbrich, C. Dietrich, H. Schirmeier, D. Lohmann, and W.
  Schröder-Preikschat. Experiences with software-based soft-error mitigation
  using AN codes. Software Quality Journal, pages 1–27, 2015.

- I. Stilkerich, P. Taffner, C. Erhardt, C. Dietrich, C. Wawersich, and
  M. Stilkerich. Team Up: Cooperative Memory Management in Embedded
  Systems.  In Proceedings of the 2014 Conference on Compilers,
  Architectures and Synthesis for Embedded Systems (CASES '14). ACM,
  October 2014.

- H. Schirmeier, C. Borchert, and O. Spinczyk. Rapid fault-space exploration by
  evolutionary pruning. In Proceedings of the 33rd International Conference on
  Computer Safety, Reliability and Security (SAFECOMP '14), Lecture Notes in
  Computer Science, pages 17–32. Springer-Verlag, Sept. 2014.

- Björn Döbel. Operating System Support for Redundant Multithreading.
  Dissertation, Technische Universität Dresden, August 2014.

- Peter Ulbrich. Ganzheitliche Fehlertoleranz in eingebetteten
  Softwaresystemen. Dissertation, Friedrich-Alexander-Universität
  Erlangen-Nürnberg, August 2014.

- M. Hoffmann, C. Borchert, C. Dietrich, H. Schirmeier, R. Kapitza, O.
  Spinczyk, and D. Lohmann. Effectiveness of fault detection mechanisms in
  static and dynamic operating system designs. In Proceedings of the 17th IEEE
  International Symposium on Object-Oriented Real-Time Distributed Computing
  (ISORC '14), pages 230–237. IEEE Computer Society Press, June 2014.

- H. Schirmeier, L. Rademacher, and O. Spinczyk. Smart-hopping: Highly efficient
  ISA-level fault injection on real hardware. In Proceedings of the 19th IEEE
  European Test Symposium (ETS '14), pages 69–74. IEEE Computer Society Press,
  May 2014.

- M. Hoffmann, P. Ulbrich, C. Dietrich, H. Schirmeier, D. Lohmann, and W.
  Schröder-Preikschat. A practitioner's guide to software-based soft-error
  mitigation using AN-codes. In Proceedings of the 15th IEEE International
  Symposium on High Assurance Systems Engineering (HASE '14), pages 33–40,
  Miami, Florida, USA, Jan. 2014. IEEE Computer Society Press.

- C. Borchert, H. Schirmeier, and O. Spinczyk. Return-address
  protection in C/C++ code by dependability aspects. In Proceedings of
  the 2nd GI Workshop on Software-Based Methods for Robust Embedded
  Systems (SOBRES '13), Lecture Notes in Informatics. German Society
  of Informatics, Sept. 2013.

- M. Hoffmann, C. Dietrich, and D. Lohmann. Failure by design:
  Influence of the RTOS interface on memory fault resilience. In
  Proceedings of the 2nd GI Workshop on Software-Based Methods for
  Robust Embedded Systems (SOBRES '13), Lecture Notes in
  Informatics. German Society of Informatics, Sept. 2013.

- I. Stilkerich, M. Strotz, C. Erhardt, M. Hoffmann, D. Lohmann, F.
  Scheler, and W. Schröder-Preikschat. A JVM for Soft-Error-Prone
  Embedded Systems. In Proceedings of the 2013 ACM SIGPLAN/SIGBED
  Conference on Languages, Compilers and Tools for Embedded Systems
  (LCTES '13), pages 21–32, June 2013.

- C. Borchert, H. Schirmeier, and O. Spinczyk. Generative
  software-based memory error detection and correction for operating
  system data structures. In Proceedings of the 43rd IEEE/IFIP
  International Conference on Dependable Systems and Networks (DSN
  '13). IEEE Computer Society Press, June 2013.

- H. Schirmeier, I. Korb, O. Spinczyk, and M. Engel. Efficient online
  memory error assessment and circumvention for Linux with RAMpage.
  International Journal of Critical Computer-Based Systems,
  4(3):227–247, 2013. Special Issue on PRDC 2011 Dependable Architecture
  and Analysis.

- B. Döbel, H. Schirmeier, and M. Engel. Investigating the limitations
  of PVF for realistic program vulnerability assessment. In Proceedings
  of the 5rd HiPEAC Workshop on Design for Reliability (DFR '13),
  Berlin, Germany, Jan. 2013.

- C. Borchert, H. Schirmeier, and O. Spinczyk. Protecting the dynamic
  dispatch in C++ by dependability aspects. In Proceedings of the 1st
  GI Workshop on Software-Based Methods for Robust Embedded Systems
  (SOBRES '12), Lecture Notes in Informatics, pages 521–535. German
  Society of Informatics, Sept. 2012.
