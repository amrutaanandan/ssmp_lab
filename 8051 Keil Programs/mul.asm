;multiplication using register indirect mode
org 00h
  mov r0, 40h
  mov r1, 50h
  mov a, @r0
  mov b, @r1
  mul ab
  end
