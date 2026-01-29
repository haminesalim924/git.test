function valider(){
    
    let nom = document.getElementById("nom").value;
    let email = document.getElementById("email").value;
    let mdp = document.getElementById("mdp").value;
    let cmdp = document.getElementById("cmdp").value;
    let age = document.getElementById("age").value;
    document.getElementById("errNom").innerHTML = "";
    document.getElementById("errEmail").innerHTML = "";
    document.getElementById("errMdp").innerHTML = "";
    document.getElementById("errCmdp").innerHTML = "";
    document.getElementById("errAge").innerHTML = "";
    document.getElementById("resultat").innerHTML = "";
    let ok = true;

    if (nom === "") {
        document.getElementById("errNom").innerHTML = "Nom obligatoire";
        ok = false;
    }

    if (!email.includes("@")) {
        document.getElementById("errEmail").innerHTML = "Email invalide";
        ok = false;
    }

    if (mdp.length < 8) {
        document.getElementById("errMdp").innerHTML = "Minimum 8 caractères";
        ok = false;
    }

    if (mdp !== cmdp) {
        document.getElementById("errCmdp").innerHTML = "Mots de passe différents";
        ok = false;
    }

    if (age < 18 || age === "") {
        document.getElementById("errAge").innerHTML = "Vous devez avoir 18 ans";
        ok = false;
    }

    if (ok) {
        document.getElementById("resultat").innerHTML =
            "<span class='success'>Inscription réussie ✅</span>";
    }
}
