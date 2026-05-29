
function R(x, y, l)
  local r = (l/2)
  return Rect(vec2f(x-r, y-r), vec2f(x+r, y+r))
end

local r1 = R(50, 50, 50)

-- add(r1)
play(Shift(r1, vec2f(200, 0), 1))
-- play(Shift(r1, vec2f(0, 200), 1))
-- play(Shift(r1, vec2f(200, 200), 1))
-- play(Shift(r1, vec2f(-300, -300), 1))

