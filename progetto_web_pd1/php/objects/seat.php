<?php
class Seat {
    private $id;
    private $user;
    private $status;
    
    function __construct($id, $user, $status) {
        $this->id = $id;
        $this->user = $user;
        $this->status = $status;    /* status of the seat, it can be:
                                     * - 0 : for free seat
                                     * - 1 : for booked seat
                                     * - 2 : for purchased seat
                                     */
    }
    
    function getId() {
        return $this->id;
    }
    
    function getUser() {
        return $this->user;
    }
     
    function getStatus() {
        return $this->status;
    }
    
    function setStatus($status) {
        if (in_array($status, array(0, 1, 2))) {
            $this->status = $status;
        }
    }
    
    
}
?>