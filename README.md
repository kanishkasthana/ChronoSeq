
# Software and Protocols for ChronoSeq

### Getting Started with Software 
+ Install [Git X86-64-Bit for Windows](https://git-scm.com/download/win) and [Anaconda X86-64-Bit for Windows](https://www.anaconda.com/download), on your [Windows X86-64 Bit PC](Computer%20Selection.md).
+ Type "Git Bash" in the Search bar next to the Start Button. Using Git Bash clone this repository.
    + Using Git Bash [Navigate to the directory](https://tutorials.codebar.io/command-line/introduction/tutorial.html) where you want to store this repository.
    + This repository has submodules. In Git Bash, use the command ```> git clone --recursive https://github.com/kanishkasthana/ChronoSeq.git```  when cloning this repository so the submodules are also cloned.
+ Type "Anaconda Prompt" in the Search bar next to the Start Button. Now create a [new environment](https://conda.io/projects/conda/en/latest/user-guide/tasks/manage-environments.html#creating-an-environment-from-an-environment-yml-file) called Chrono from [this file](conda_environment_file/chrono.env.yml)
+ [Activate the Environment](https://docs.conda.io/projects/conda/en/latest/user-guide/tasks/manage-environments.html#activating-an-environment) from the Anaconda Prompt. 
+ Using the Anaconda Prompt navigate to the directory for the git repository you cloned.
    + Alternatively you can modify your Anaconda Prompt shortcut so that it always activates the Chrono Environment and launches at the location of your Git repository. I've included [an example here](conda_environment_file/Anaconda%20Prompt.lnk).
    + Open Run and type ```shell:startup``` to open your startup folder.<br><img src="img/Screenshot%202024-10-24%20184651.png">
    + You can copy the shortcut included to this startup folder.
    + Then right click the shortcut and change the ```Target``` and ```Start In``` sections so that a command line terminal with the environment automatically activated opens during startup.<br><img src="img/Screenshot%202024-10-24%20184946.png">
+ Using Anaconda Prompt Run ```> jupyter notebook``` 
+ The links to the notebooks below are intended to be opened using Jupyter. Click the image below to watch a video of the process.
<br>[<img src="https://img.youtube.com/vi/qbhCONpUdx0/hqdefault.jpg">](https://www.youtube.com/watch?v=qbhCONpUdx0)

### Overview of Technology and Workflow
+ [This notebook](ChronoSeq_Overview.ipynb) provides an overview of ChronoSeq technology. 

### Device Assembly
+ See the [Device Assembly and Setup notebook](instructions_for_device_assembly_and_setup.ipynb) for a detailed description of how to set everything up.

### Storage of Dropseq beads upon receipt
+ You should receive your beads suspended in Ethanol.
+ Store these beads in a new box at -20&deg;C before you start your experiments or for long term storage. Label the box with the Date you received the beads, the bead type and the batch number.

### Running the Device and Preparation for Experiment
+ Once you are ready, see [this notebook](protocol_and_software_for_running_chronoseq_device.ipynb#Protocol-for-Preparation-and-Operation-of-the-ChronoSeq-Device-for-an-Experiment.) on how to run the Device and the preparation needed.

### Videos of Device Operation
+ Click the image below to watch a video of the view from inside the microfluidic chip during an Injection.<br>[<img src="https://img.youtube.com/vi/J2O1kA4chU0/hqdefault.jpg">](https://www.youtube.com/watch?v=J2O1kA4chU0)
+ Click the image below to watch an outside view of the ChronoSeq device during an Injection. <br>[<img src="https://img.youtube.com/vi/qFouf2HrKSk/hqdefault.jpg">](https://www.youtube.com/watch?v=qFouf2HrKSk)

### Build Compilation Music Video
+ Click the image below to watch a music video of the iteration/build process for making the ChronoSeq device.<br>[<img src="https://img.youtube.com/vi/QpMUR4AgpgA/hqdefault.jpg">](https://www.youtube.com/watch?v=QpMUR4AgpgA)

# License

We have released this work under a [CC BY-NC-SA 4.0 License](LICENSE).

# Disclaimer

Dear Fellow Users and Researchers,
<br><br>
We are thrilled that you are interested in assembling the ChronoSeq Device we have created. However, it is important to note that we cannot be held responsible for any injuries that may occur during the assembly and operation process.<br>
While we strive to provide clear and concise instructions, the assembly of this open source hardware requires a certain level of skill and experience. Therefore, we strongly recommend that you take all necessary precautions to ensure your safety.<br>
Please read and follow all instructions carefully, and make sure that you have the necessary tools and protective equipment. If you are unsure about any step or procedure, do not hesitate to seek the advice of a qualified professional. You are also welcome to raise [an issue on the Github repo](https://github.com/kanishkasthana/ChronoSeq/issues) if you have any questions or if anything is unclear.<br> 
<br>
By using or constructing this open source hardware design, you acknowledge and agree to the following:
1. Liability Waiver: The creators, designers, and contributors of this open source hardware project cannot be held liable for any injuries, damages, or losses resulting from the use, construction, or modification of this hardware.
2. Assumption of Risk: You, as the builder or user, assume all risks associated with the construction, use, and modification of this hardware. This includes, but is not limited to, personal injury, property damage, or any other potential harm.
3. Waiver of Legal Action: By proceeding with the use or construction of this open source hardware, you waive your right to sue, hold legally responsible, or seek compensation from the creators, designers, or contributors for any reason related to this project.
4. No Warranty: This open source hardware is provided "as is" without any express or implied warranties. The creators make no guarantees regarding its safety, functionality, or fitness for any particular purpose.
5. Responsibility: You are solely responsible for ensuring that you follow all safety precautions, local laws, and regulations when building or using this hardware.
6. Modifications: Any modifications you make to the original design are your sole responsibility, and the original creators bear no liability for the results of such modifications.
<br>By proceeding with the use or construction of this open source hardware, you indicate your understanding and acceptance of these terms.

Thank you for choosing our open source hardware, and we hope that you enjoy the building and operation process.
<br><br>
Best regards,
<br>ChronoSeq Team:
<br>Kanishk Asthana [kasthana@ucsd.edu](mailto:kasthana@ucsd.edu)
<br>Wei Wang [wei-wang@ucsd.edu](mailto:wei-wang@ucsd.edu)

# Data Processing and Analysis

+ Check out the [ChronoSeq Tools repo](https://github.com/kanishkasthana/ChronoSeq-Tools) to help analyse your data.