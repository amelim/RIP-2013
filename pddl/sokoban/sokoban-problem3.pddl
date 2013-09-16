(define (problem sokoban_problem3)
  (:domain sokoban-domain)
  (:objects
      down - direction
      left - direction
      right - direction
      up - direction
      r - robot
      b1 - box
      b2 - box
      b3 - box
      s-2-5 - location
      s-2-6 - location
      s-2-7 - location
      s-3-5 - location
      s-3-7 - location
      s-4-5 - location
      s-4-6 - location
      s-4-7 - location
      s-5-5 - location
      s-5-7 - location
      s-6-5 - location
      s-6-6 - location
      s-6-7 - location
      s-7-5 - location
      s-7-7 - location
      s-8-2 - location
      s-8-3 - location
      s-8-4 - location
      s-8-5 - location
      s-8-6 - location
      s-8-7 - location
      s-9-2 - location
      s-9-5 - location
      s-10-2 - location
      s-10-3 - location
      s-10-4 - location
      s-10-5 - location
  )
  (:init
     (at r s-3-5)
     (at b1 s-5-5)
     (at b2 s-7-5)
     (at b3 s-9-5)
     (empty s-2-5)
     (empty s-2-6)
     (empty s-2-7)
     (empty s-3-7)
     (empty s-4-5)
     (empty s-4-6)
     (empty s-4-7)
     (empty s-5-7)
     (empty s-6-5)
     (empty s-6-6)
     (empty s-6-7)
     (empty s-7-7)
     (empty s-8-2)
     (empty s-8-3)
     (empty s-8-4)
     (empty s-8-5)
     (empty s-8-6)
     (empty s-8-7)
     (empty s-9-2)
     (empty s-10-2)
     (empty s-10-3)
     (empty s-10-4)
     (empty s-10-5)
     (adjacent s-2-5 s-3-5 right)
     (adjacent s-3-5 s-2-5 left)
     (adjacent s-2-7 s-3-7 right)
     (adjacent s-3-7 s-2-7 left)
     (adjacent s-3-5 s-4-5 right)
     (adjacent s-4-5 s-3-5 left)
     (adjacent s-3-7 s-4-7 right)
     (adjacent s-4-7 s-3-7 left)
     (adjacent s-4-5 s-5-5 right)
     (adjacent s-5-5 s-4-5 left)
     (adjacent s-4-7 s-5-7 right)
     (adjacent s-5-7 s-4-7 left)
     (adjacent s-5-5 s-6-5 right)
     (adjacent s-6-5 s-5-5 left)
     (adjacent s-5-7 s-6-7 right)
     (adjacent s-6-7 s-5-7 left)
     (adjacent s-6-5 s-7-5 right)
     (adjacent s-7-5 s-6-5 left)
     (adjacent s-6-7 s-7-7 right)
     (adjacent s-7-7 s-6-7 left)
     (adjacent s-7-5 s-8-5 right)
     (adjacent s-8-5 s-7-5 left)
     (adjacent s-7-7 s-8-7 right)
     (adjacent s-8-7 s-7-7 left)
     (adjacent s-8-2 s-9-2 right)
     (adjacent s-9-2 s-8-2 left)
     (adjacent s-8-5 s-9-5 right)
     (adjacent s-9-5 s-8-5 left)
     (adjacent s-9-2 s-10-2 right)
     (adjacent s-10-2 s-9-2 left)
     (adjacent s-9-5 s-10-5 right)
     (adjacent s-10-5 s-9-5 left)
     (adjacent s-2-5 s-2-6 up)
     (adjacent s-2-6 s-2-5 down)
     (adjacent s-2-6 s-2-7 up)
     (adjacent s-2-7 s-2-6 down)
     (adjacent s-4-5 s-4-6 up)
     (adjacent s-4-6 s-4-5 down)
     (adjacent s-4-6 s-4-7 up)
     (adjacent s-4-7 s-4-6 down)
     (adjacent s-6-5 s-6-6 up)
     (adjacent s-6-6 s-6-5 down)
     (adjacent s-6-6 s-6-7 up)
     (adjacent s-6-7 s-6-6 down)
     (adjacent s-8-2 s-8-3 up)
     (adjacent s-8-3 s-8-2 down)
     (adjacent s-8-3 s-8-4 up)
     (adjacent s-8-4 s-8-3 down)
     (adjacent s-8-4 s-8-5 up)
     (adjacent s-8-5 s-8-4 down)
     (adjacent s-8-5 s-8-6 up)
     (adjacent s-8-6 s-8-5 down)
     (adjacent s-8-6 s-8-7 up)
     (adjacent s-8-7 s-8-6 down)
     (adjacent s-10-2 s-10-3 up)
     (adjacent s-10-3 s-10-2 down)
     (adjacent s-10-3 s-10-4 up)
     (adjacent s-10-4 s-10-3 down)
     (adjacent s-10-4 s-10-5 up)
     (adjacent s-10-5 s-10-4 down)
  )
  (:goal (and
             (at b3 s-8-2)
             (at b2 s-8-3)
             (at b1 s-8-4)
         )
  )
)
