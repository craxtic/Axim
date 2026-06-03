# Tasks

- [x] refine `README.md`

---
- [ ] write an xml parser for lua
- [ ] write lua script to only output failed test cases followed by expression.
- [ ] write lua script to only output the benchmarkk test cases
- [ ] find a way to keep track of resource usage
- [ ] find a way to keep track of
  1. number of draw calls
  2. flush count
  3. copy count
  4. 
  5. ...
- [x] implement arena allocation `axim/core/allocator`
- [x] impelment block (linked-list of allocator) `axim/core/cloud`

---
## lua bindings
- [x] move from `sol2` to `luajit ffi`
- [x] bind `Mobject`, `VMobject`, `Rect`
- [x] bind `Shift` animation

### bugs.fix
- [ ] pass null object from lua causes crash



## Mobjects
- [ ] `Polygon` : `VMobject`  
  restructure `Rect` : `Polygon`
- [ ] `TipableVM` : `VMobject`
- [ ] `Line` : `TipableVM`
- [ ] `Arc` : `TipableVM`
- [ ] `Circle` : `Arc`
- [ ] `SVG` : `VMobject`
- [ ] `Text` :  `SVG`


## Renderer
- [ ] make the Renderer listen to the Canvas
  Canvas should be the one who decides width, height, bg_color, ...
- [ ] refine the interation between classes
  must be clear, clean and maintainable.

- [ ] make `Renderer::submit` accepts const std::span<>& instead of std::vector<>&
- [ ] forward declaration all possible types.
  - Shader
  - Canvas