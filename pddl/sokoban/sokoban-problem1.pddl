(define (problem sokoban_problem0)
  (:domain sokoban-domain)
  (:objects
      down - direction
      left - direction
      right - direction
      up - direction
      r - robot
      b1 - box
      s-2-2 - location
      s-2-4 - location
      s-2-5 - location
      s-2-6 - location
      s-3-2 - location
      s-3-3 - location
      s-3-4 - location
      s-3-5 - location
      s-3-6 - location
      s-4-4 - location
      s-4-5 - location
      s-5-4 - location
      s-5-5 - location
  )
  (:init
     (at r s-3-3)
     (at b1 s-4-5)
     (empty s-2-2)
     (empty s-2-4)
     (empty s-2-5)
     (empty s-2-6)
     (empty s-3-2)
     (empty s-3-4)
     (empty s-3-5)
     (empty s-3-6)
     (empty s-4-4)
     (empty s-5-4)
     (empty s-5-5)
     (adjacent s-2-2 s-3-2 right)
     (adjacent s-3-2 s-2-2 left)
     (adjacent s-2-4 s-3-4 right)
     (adjacent s-3-4 s-2-4 left)
     (adjacent s-2-5 s-3-5 right)
     (adjacent s-3-5 s-2-5 left)
     (adjacent s-2-6 s-3-6 right)
     (adjacent s-3-6 s-2-6 left)
     (adjacent s-3-4 s-4-4 right)
     (adjacent s-4-4 s-3-4 left)
     (adjacent s-3-5 s-4-5 right)
     (adjacent s-4-5 s-3-5 left)
     (adjacent s-4-4 s-5-4 right)
     (adjacent s-5-4 s-4-4 left)
     (adjacent s-4-5 s-5-5 right)
     (adjacent s-5-5 s-4-5 left)
     (adjacent s-2-4 s-2-5 up)
     (adjacent s-2-5 s-2-4 down)
     (adjacent s-2-5 s-2-6 up)
     (adjacent s-2-6 s-2-5 down)
     (adjacent s-3-2 s-3-3 up)
     (adjacent s-3-3 s-3-2 down)
     (adjacent s-3-3 s-3-4 up)
     (adjacent s-3-4 s-3-3 down)
     (adjacent s-3-4 s-3-5 up)
     (adjacent s-3-5 s-3-4 down)
     (adjacent s-3-5 s-3-6 up)
     (adjacent s-3-6 s-3-5 down)
     (adjacent s-4-4 s-4-5 up)
     (adjacent s-4-5 s-4-4 down)
     (adjacent s-5-4 s-5-5 up)
     (adjacent s-5-5 s-5-4 down)
  )
  (:goal (and
             (at b1 s-3-2)
         )
  )
)
