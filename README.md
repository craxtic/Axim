# Axim

> **_Where logic finds its rhythm and every line of code begins to dance._**

Modern animation often feels trapped between two worlds: the manual labor of visual editors and the rigid complexity of low-level graphics code. 
**Axim** is an animation framework designed to bridge this gap. 
It is a world where mathematical precision meets creative fluidity, enabling you to script complex, high-fidelity motion graphics using the capability of C++ and the simplicity of Lua. 

Whether you are visualizing a theorem, creating explainary mathematics or science animation, or generating automated video content,
Axim provides the tools to turn abstract concepts in your imagination into an absolute cinematic reality.

---

### Mission
To provide a high-performance, programmable motion graphics framework that unites the performance of C++ with the expressive agility of Lua. By leveraging a custom 2D vector engine and FFmpeg’s encoding power, Axim allows developers to build mathematically precise, general-purpose animations through a streamlined, scriptable workflow.

---

### Tech Stack
* **Scripting**: Lua integration for rapid animating and creative live-coding.
* **Preview**: SDL3 for a responsive, real-time visual feedback window.
* **Export**: FFmpeg pipeline for high-fidelity video encoding.
* **Rendering**: A custom rendering engine built on top of BGFX for hardware-accelerated.
* **Core**: A custom C++ library built for motion, easing, and geometry.

---

###  Key Features
* **General-Purpose Motion**: Not limited to math or science; built for any visual narrative that can be described by logic.
* **Live Preview**: Tweak your Lua scripts and see your logic "dance" update instantly via the SDL3 window.
* **Programmatic Precision**: Every frame is backed by a rigorous C++ math core, ensuring perfect reproducibility.
* **Headless Export**: Seamlessly transition from a live window to a finished video file via FFmpeg.
* **Embeddable**: Axim provide an interface called `PresenterInterface` which can be used to custom your own presenter (an output target) in many applications. This interface is, by default, implemented by `PreviewPresenter`, which is the preview window (SDL3) and `ExportPresenter`, which is the export class (ffmpeg).

> Axim is currently in its early stage of development, so it's not yet considered to be ready for production use.

### The actual purpose
Hi everyone, and hope you're doing well, **Axim** is not originally created to be a production grade animation engine.
My purpose was just to learn new things, especially explore graphic programming as a way to turn the maths I studied into art. I consider this as a really great opportunity as well as an interesting adventure for me as a computer science student. The true value of learning lies in the adventure, doesn't it? Then I have a reason to not give up, at least not now :]  
This project was inspired by **Manim**, one of the best math animation engine, while my **Axim** is just a beginner's playground, i still have a very very long way to go. 


###  License
This project is licensed under the MPL 2.0 License.
> for third-parties, see licenses/