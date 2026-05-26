add_rules("mode.debug", "mode.release")
set_languages("c++23")

includes("xmake/bgfx_rules.lua")

add_requires("bgfx")
add_requires("libsdl3")
add_requires("luajit")
add_requires("catch2") 


--- for development
add_includedirs("$(projectdir)/include") ---
add_includedirs("$(projectdir)/app/include")
set_warnings("allextra")
set_policy("build.warning", true)

-- local function format_path_for_defines(_define, _path) 
--   -- local __path = path.join(os.projectdir(), "lua")
--   if is_host("windows") then
--     return _define .. '"' .. _path:gsub("\\", "\\\\") .. '"'
--   else
--     return _define .. '"' .. _path .. '"'
--   end
-- end

-- ----




--- @axim-core
--- 
target("axim-core") do 
  set_kind("shared")
  set_symbols("hidden")
  add_defines("AXIM_CORE_EXPORTS")
  add_files("src/core/**.cpp")
end



target("axim-shaders") do
  set_kind("object")
  add_rules("local.bgfx.shaders")
  add_packages("bgfx")

  add_files("src/renderer/shaders/**.frag")
  add_files("src/renderer/shaders/**.vert")

  add_includedirs("external/bgfx")

end


--- @axim-renderer
target("axim-renderer") do
  set_kind("shared")
  set_symbols("hidden")
  add_defines("AXIM_RENDERER_EXPORTS")
  add_files("src/renderer/**.cpp")

  add_deps("axim-shaders")
  add_packages("bgfx")

  after_load(function (target) 
    local dep = target:dep("axim-shaders")
    if dep then 
      target:add("defines", 'AXIM_SHADERS_DIR="' .. dep:targetdir() .. '/shaders"')
    end 
    -- add_defines("AXIM_SHADERS_DIR=".. path.join(target:targetdir(), "shaders"))
  end)

end


--- @axim-engine
--- the rendering engine
target("axim-engine") do
  set_kind("shared")
  set_symbols("hidden")
  add_defines("AXIM_ENGINE_EXPORTS")
  add_files("src/engine/**.cpp")
  
  add_deps("axim-renderer")
end



--- @axim-presenter
--- provide presenter to output frames rendered by the engine 
--- either preview, export, or integrate into an external enviroment
target("axim-presenters") do
  set_kind("shared")
  set_symbols("hidden")
  add_defines("AXIM_PRESENTER_EXPORTS")
  add_files("src/presenter/**.cpp")
  
  add_packages("libsdl3")
end


--- @axim-app
--- the application command-line interface
target("axim") do 
  set_kind("binary")
  add_files("app/src/**.cc")
  add_deps("axim-core", "axim-renderer", "axim-engine", "axim-presenters")

  if is_plat("linux", "bsd") then
    add_ldflags("-rdynamic", {force = true})
  end

  add_packages("libsdl3", "luajit")

  add_defines("AXIM_LUA_DIR=\"$(projectdir)/lua\"")
end




--- @axim-test
--- compile every test files, run and write to test/reports/name.xml
for _, file in ipairs(os.files("test/src/**.cxx")) do
  local name = path.basename(file)

  target(name) do
    set_kind("binary")
    set_default(false)
    add_files(file)
    add_packages("catch2")
    
    before_test(function () 
      os.mkdir("test/reports")
    end)

    add_tests("test", {
      runargs = {
        "-r", "xml", 
        "-o", path.join(os.projectdir(), "test", "reports", name .. ".xml")
      }
    })
    
  end
end



--- @axim-report
--- parse the test/reports/*.xml and report test results
task("report") do
  on_run(function ()
    local paths = path.join(os.projectdir(), "test", "reports", "*.xml")
    for _, file in ipairs(os.files(paths)) do
      -- print("FILE: " .. file)
      os.execv("lua", {"test/output-reports.lua", file})
      
    end
  end)

  set_menu {
    usage = "xmake report [options]",
    description = "View full test results.",
    options = {
      "-c", 
    }
  }
end


