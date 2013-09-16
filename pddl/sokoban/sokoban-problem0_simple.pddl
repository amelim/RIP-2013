(define (problem sokoban-problem0_simple)
  (:domain sokoban-domain)
  (:objects
    down - direction
    left - direction
    right - direction
    up - direction
    r - robot
    s-2-2 - location
    s-2-3 - location
    s-2-4 - location
    s-3-2 - location
    s-3-3 - location
    s-3-4 - location
    s-4-2 - location
    s-4-3 - location
    s-4-4 - location
  )
  (:init
  	(at r s-2-2)
    (adjacent s-2-2 s-3-2 right)
    (adjacent s-3-2 s-2-2 left)
    (adjacent s-2-3 s-3-3 right)
    (adjacent s-3-3 s-2-3 left)
    (adjacent s-2-4 s-3-4 right)
    (adjacent s-3-4 s-2-4 left)
    (adjacent s-3-2 s-4-2 right)
    (adjacent s-4-2 s-3-2 left)
    (adjacent s-3-3 s-4-3 right)
    (adjacent s-4-3 s-3-3 left)
    (adjacent s-3-4 s-4-4 right)
    (adjacent s-4-4 s-3-4 left)
    (adjacent s-2-2 s-2-3 up)
    (adjacent s-2-3 s-2-2 down)
    (adjacent s-2-3 s-2-4 up)
    (adjacent s-2-4 s-2-3 down)
    (adjacent s-3-2 s-3-3 up)
    (adjacent s-3-3 s-3-2 down)
    (adjacent s-3-3 s-3-4 up)
    (adjacent s-3-4 s-3-3 down)
    (adjacent s-4-2 s-4-3 up)
    (adjacent s-4-3 s-4-2 down)
    (adjacent s-4-3 s-4-4 up)
    (adjacent s-4-4 s-4-3 down)
	(empty s-2-2)
    (empty s-2-4)
    (empty s-3-2)
    (empty s-3-3)
    (empty s-3-4)
    (empty s-4-2)
    (empty s-4-4)  
  )
  (:goal (at r s-4-4)
  )
)
