;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Sokoban Domain Definition
;; Sept 12, 2013
;; Andrew Melim, Daniel Pickem, Jarius Tilman

(define (domain sokoban-domain)
  (:requirements :equality)
  (:predicates (robot ?r) (box ?b) (robot_at ?l) (object_at ?b ?l)
               (adjacent ?from ?to ?dir) (empty ?loc))
  (:action move
    :parameters (?r ?from ?to ?dir)
    :precondition (and (robot ?r) (empty ?to) (robot_at ?from)
                   (adjacent ?from ?to ?dir))
    :effect (and (robot_at ?to) (not (empty ?to)) 
             (empty ?from) (not (robot_at ?from))))

  (:action push
    :parameters (?r ?box ?rloc ?bloc ?tloc ?dir)
    :precondition (and (robot ?r) (box ?b) (empty ?tloc)
                   (robot_at ?rloc) (box_at ?bloc))
    :effect (and (robot_at ?bloc) (not (robot_at ?rloc))
             (box_at ?tloc) (not (box_at ?bloc)) 
             (empty ?rloc) (not (empty ?tloc))))


)
