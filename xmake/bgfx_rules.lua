
rule("local.bgfx.shaders")
  set_extensions(".sc", ".vert", ".frag", ".comp")
  on_buildcmd_file(function(target, batchcmds, shaderfile, opt)
    import("lib.detect.find_program")
    import("core.base.option")

    batchcmds:show_progress(opt.progress, "${color.build.object}compiling.shaderc %s", shaderfile)

    -- get bgfx shaderc
    local shaderc = find_program("shadercRelease") or find_program("shadercDebug")
        or find_program("shaderc") or find_program("bgfx-shaderc")
    assert(shaderc, "bgfx shaderc not found! please check your bgfx installation.")


    local output_filename = path.filename(shaderfile) .. ".bin"
    local output_dir = path.join(target:targetdir(), "shaders")
    local vardef_filename = path.join(path.directory(shaderfile), "varying.def.sc")
  

    -- determine platform-specific shaderc arguments
    local bgfx_platforms = {
      windows = "windows",
      macosx = "osx",
      linux = "linux"
    }
    local bgfx_default_profiles = {
      windows = "s_5_0",
      macosx = "metal",
      linux = "spirv"
    }

    local shader_type
    if shaderfile:match("^vs_.*%.sc$") or shaderfile:match("%.vert$") then
      shader_type = "vertex"
    elseif shaderfile:match("^fs_.*%.sc$") or shaderfile:match("%.frag$") then
      shader_type = "fragment"
    elseif shaderfile:match("^cs_.*%.sc$") or shaderfile:match("%.comp$") then
      shader_type = "compute"
    else
      raise("cannot determine shader type from file name " .. path.filename(shaderfile))
    end

    -- build command args
    local args = {
      "-f", shaderfile, "--type", shader_type, "--varyingdef", vardef_filename,
      "--platform", bgfx_platforms[target:plat()],
    }

    for _, includedir in ipairs(target:get("includedirs")) do
      table.insert(args, "-i")
      table.insert(args, includedir)
    end

    local mtime = 0
    local shader_profile = bgfx_default_profiles[target:plat()]
    batchcmds:mkdir(output_dir)
    local binary =  path.join(output_dir, output_filename)

    -- compiling
    table.insert(args, "-o")
    table.insert(args, binary)
    table.insert(args, "--profile")
    table.insert(args, shader_profile)
    if option.get("verbose") then
      batchcmds:show(shaderc .. " " .. os.args(args))
    end
    batchcmds:vrunv(shaderc, args)

    if (mtime == 0) then mtime = os.mtime(binary) end
    -- end

    -- add deps
    batchcmds:add_depfiles(shaderfile)
    batchcmds:set_depmtime(mtime)
  end)
