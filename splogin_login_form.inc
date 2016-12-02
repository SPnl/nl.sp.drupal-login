<?php

/*
 * SPNET alternative login form
 */

function splogin_login_form($form, &$form_state) {

  form_load_include($form_state, 'inc', 'content', 'includes/password');

  $form['#attached']['css'] = array(
    drupal_get_path('module', 'splogin') . '/css/splogin.css',
  );

  if (!isset($form_state['stages'])) {
    $form_state['stages'][] = 'start';
  }
  $stage = end($form_state['stages']);
  $stored_data = (isset($form_state['stored_data'])) ? $form_state['stored_data'] : array();

  switch($stage) {

  case 'start':

    $title = 'Aanmelden';
    $default = (isset($stored_data['contact_id'])) ? $stored_data['contact_id'] : '';

    $form['start_intro'] = array(
      '#markup' => '<p>Welkom op het SPnet, de ledensite van de SP.</p><p>Meld je hier aan voor toegang tot SPNET.</p>',
    );

    $form['contact_id'] = array(
      '#type'  => 'textfield',
      '#title' => t('Relatie- of lidnummer'),
      '#default_value' => $default,
      '#size' => 8,
    );

    $form['no_id_button'] = array(
      '#type' => 'submit',
      '#value' => 'Relatie- of lidnummer opvragen',
      '#name' => 'no_id_button',
      '#weight' => 1,
    );

    $form['no_member_button'] = array(
      '#type' => 'submit',
      '#value' => 'Ik ben geen lid',
      '#name' => 'no_member_button',
      '#weight' => 2,
    );

    break;

  case 'no_id':

    $title = 'Opvragen relatie- of lidnummer';

    $form['start_no_id'] = array(
      '#markup' => '<p>Vul onderstaand formulier in, dan geven we zo snel mogelijk je lidnummer door.</p>',
    );

    $form['first_name'] = array(
      '#type' => 'textfield',
      '#title' => 'Voornaam',
      '#size' => 20,
    );

    $form['middle_name'] = array(
      '#type' => 'textfield',
      '#title' => 'Tussenvoegsel(s)',
      '#size' => 6,
    );

    $form['last_name'] = array(
      '#type' => 'textfield',
      '#title' => 'Achternaam',
      '#size' => 30,
    );

    $default = (isset($stored_data['birth_date'])) ? $stored_data['birth_date'] : '';
    $form['birth_date'] = array(
      '#type' => 'date_select',
      '#title' => 'Geboortedatum',
      '#date_format' => 'd-m-Y',
      '#date_year_range' => '-110:-13',
      '#default_value' => $default,
    );

    $form['street_and_number'] = array(
      '#type' => 'textfield',
      '#title' => 'Adres',
      '#size' => 40,
    );

    $default = (isset($stored_data['postal_code'])) ? $stored_data['postal_code'] : '';
    $form['postal_code'] = array(
      '#type' => 'textfield',
      '#title' => 'Postcode',
      '#size' => 7,
      '#default_value' => $default,
    );

    $form['locality'] = array(
      '#type' => 'textfield',
      '#title' => 'Plaats',
      '#size' => 40,
    );

    $default = (isset($stored_data['email'])) ? $stored_data['email'] : '';
    $form['email'] = array(
      '#type' => 'textfield',
      '#title' => 'E-mailadres',
      '#size' => 40,
      '#default_value' => $default,
    );

    $form['telephone'] = array(
      '#type' => 'textfield',
      '#title' => 'Telefoonnummer',
      '#size' => 14,
    );

    $form['foreign_message'] = array(
      '#markup' => '<p>* Woont u buiten Nederland, neem dan contact op met onze administratie afdeling: tel (+31) (0)88 243 55 40</p>',
    );

    break;

  case 'has_account':
    
    $title = 'Aanmelden';
    $default = (isset($stored_data['contact_id'])) ? $stored_data['contact_id'] : '';
    $form['contact_id'] = array(
      '#type'  => 'textfield',
      '#title' => t('Relatie- of lidnummer'),
      '#default_value' => $default,
      '#size' => 8,
    );

    $form['pass'] = array(
      '#type' => 'password',
      '#title' => 'Wachtwoord',
      '#size' => 10,
    );

    $form['pass_reset_button'] = array(
      '#type' => 'submit',
      '#value' => 'Nieuw wachtwoord instellen',
      '#name' => 'pass_reset_button',
      '#weight' => 1,
    );

    break;

  case 'no_account':

    $title = 'Controle persoonsgegevens';
    $form['intro_no_account'] = array(
      '#markup' => '<p>Om te voorkomen dat iemand anders als jou kan inloggen controleren we je postcode en geboortedatum.</p>',
    );

    $default = (isset($stored_data['postal_code'])) ? $stored_data['postal_code'] : '';
    $form['postal_code'] = array(
      '#type' => 'textfield',
      '#title' => 'Postcode',
      '#default_value' => $default,
      '#size' => 7,
    );

    $default = (isset($stored_data['birth_date'])) ? $stored_data['birth_date'] : '';
    $form['birth_date'] = array(
      '#type' => 'date_select',
      '#title' => 'Geboortedatum',
      '#date_format' => 'd-m-Y',
      '#date_year_range' => '-110:-13',
      '#default_value' => $default,
    );

    break;

  case 'recheck_id':

    $title = 'Controle persoonsgegevens';

    $form['check_id_intro'] = array(
      '#markup' => '<p>We kunnen jouw gegevens niet terugvinden, weet je zeker dat het onderstaande relatie- of lidnummer correct is?<br/>(Corrigeren als dat niet het geval is.)</p>',
    );

    $default = (isset($stored_data['contact_id'])) ? $stored_data['contact_id'] : '';
    $form['new_contact_id'] = array(
      '#type'  => 'textfield',
      '#title' => t('Relatie- of lidnummer'),
      '#default_value' => $default,
      '#size' => 8,
    );

    break;

  case 'account_not_verified':

    $title = 'Aanvullen persoonsgegevens';

    $form['intro_account_not_verified'] = array(
      '#prefix' => '<p>Vul hieronder je persoonsgegevens in, dan zorgt onze administratieafdeling dat je gegevens in onze administratie worden bijgewerkt, en je toegang krijgt tot SPNET. Zodra dit is geregeld ontvang je een e-mail met instructies om in te loggen.</p>',
    );

    $form['first_name'] = array(
      '#type' => 'textfield',
      '#title' => 'Voornaam',
      '#size' => 20,
    );

    $form['middle_name'] = array(
      '#type' => 'textfield',
      '#title' => 'Tussenvoegsel(s)',
      '#size' => 6,
    );

    $form['last_name'] = array(
      '#type' => 'textfield',
      '#title' => 'Achternaam',
      '#size' => 30,
    );

    $default = (isset($stored_data['birth_date'])) ? $stored_data['birth_date'] : '';
    $form['birth_date'] = array(
      '#type' => 'date_select',
      '#title' => 'Geboortedatum',
      '#date_format' => 'd-m-Y',
      '#date_year_range' => '-110:-13',
      '#default_value' => $default,
    );

    $form['street_and_number'] = array(
      '#type' => 'textfield',
      '#title' => 'Adres',
      '#size' => 40,
    );

    $default = (isset($stored_data['postal_code'])) ? $stored_data['postal_code'] : '';
    $form['postal_code'] = array(
      '#type' => 'textfield',
      '#title' => 'Postcode',
      '#size' => 7,
      '#default_value' => $default,
    );

    $form['locality'] = array(
      '#type' => 'textfield',
      '#title' => 'Plaats',
      '#size' => 40,
    );

    $form['email'] = array(
      '#type' => 'textfield',
      '#title' => 'E-mailadres',
      '#size' => 40,
    );

    $form['telephone'] = array(
      '#type' => 'textfield',
      '#title' => 'Telefoonnummer',
      '#size' => 14,
    );

    $form['foreign_message'] = array(
      '#markup' => '<p>* Woont u buiten Nederland, neem dan contact op met onze administratie afdeling: tel (+31) (0)88 243 55 40</p>',
    );

    break;

  case 'email_check':

    $form['intro_email_check'] = array(
      '#markup' => '<p>Is het e-mailadres dat we van jou hebben nog correct?</p>',
    );
  
    $title = 'Controle e-mailadres';
    $email = $stored_data['email_check'];
    $form['email_check'] = array(
      '#markup' => '<p>' . $email . '</p>',
    );

    $form['email_correct'] = array(
      '#type' => 'checkboxes',
      '#options' => array('correct' => 'E-mailadres is correct'),
    );

    break;

  case 'new_email':

    $title = 'Instellen e-mailadres';

    $form['intro_new_email'] = array(
      '#markup' => '<p>Wat is dan jouw e-mailadres?</p>',
    );

    $default = (isset($stored_data['email'])) ? $stored_data['email'] : '';
    $form['new_email'] = array(
      '#type' => 'textfield',
      '#title' => 'E-mail',
      '#size' => 40,
      '#default_value' => $default,
    );

    break;

  }

  $form['general_submit_button'] = array(
    '#type' => 'submit',
    '#value' => 'Volgende',
    '#name' => 'general_submit_button',
  );

  if (!in_array($stage, array('start', 'has_account'))) {
    $form['back_button'] = array(
      '#type' => 'submit',
      '#value' => 'Terug',
      '#name' => 'back_button',
    );
  }

  $form['#prefix'] = '<header class="content-header"><h1 class="title">' . $title . '</h1></header>';

  return $form;
}

function splogin_login_form_validate($form, &$form_state) {

  if (isset($form_state['triggering_element'])) {

    $values = $form_state['values'];
    $stored_data = &$form_state['stored_data'];
    $stages = $form_state['stages'];
    $stage = end($form_state['stages']);

    $trigger = $form_state['triggering_element']['#name'];

    switch ($trigger) {

    case 'general_submit_button':
      switch ($stage) {

      case 'start':
        if (filter_var($values['contact_id'], FILTER_VALIDATE_INT) === FALSE) {
          form_set_error('contact_id', 'Vul een geldig relatie -of lidnummer in');
        }
        break;

      case 'no_id':
        preg_match('/^([1-9][0-9]{3})[\s]?([A-Za-z]{2})$/', $values['postal_code'], $matches); 
        $postal_code = $matches[1] . ' ' . strtoupper($matches[2]);
        $values['postal_code'] = $postal_code;

        if (empty($values['first_name'])) {
          form_set_error('first_name', 'Vul je voornaam in!');
        }
        if (empty($values['last_name'])) {
          form_set_error('last_name', 'Vul je achternaam in!');
        }
        if (empty($values['birth_date'])) {
          form_set_error('birth_date', 'Vul je geboortedatum in!');
        }
        if (empty($values['street_and_number'])) {
          form_set_error('street_and_number', 'Vul je adres in!');
        }
        if (!preg_match('/^[1-9][0-9]{3}[\s]?[A-Za-z]{2}$/', $values['postal_code'])) {
          form_set_error('postal_code', 'Vul een geldige postcode in!');
        }
        if (empty($values['locality'])) {
          form_set_error('locality', 'Vul je woonplaats in!');
        }
        if (!valid_email_address($values['email'])) {
          form_set_error('email', 'Vul een geldig e-mailadres in!');
        }
        $regex_telephone_fixed = '/^(((0)[1-9]{2}[0-9][-]?[1-9][0-9]{5})|((\\+31|0|0031)[1-9][0-9][-]?[1-9][0-9]{6}))$/';
        $regex_telephone_mobile = '/^(((\\+31|0|0031)6){1}[1-9]{1}[0-9]{7})$/';
        if (!(preg_match($regex_telephone_fixed, $values['telephone']) || preg_match($regex_telephone_mobile, $values['telephone']))) {
          form_set_error('telephone', 'Vul een geldig telefoonnummer in!');
        }
        break;

      case 'has_account':
        global $_SESSION;

        // Store variables for flood control.
        $account = user_load($stored_data['drupal_account']);
        $form_state['values']['name'] = $account->name;

        // Flood control and check if user password is ok.
        user_login_authenticate_validate($form, $form_state);
        user_login_final_validate($form, $form_state);

        // Change error message.
        if (!empty($_SESSION['messages']['error'])) {
          $_SESSION['messages']['error'] = array(
            '<p>Relatie- of lidnummer of  wachtwoord is niet correct.</p>',
          );
        }

        break;

      case 'pass_reset':

        // Validate password.
        $regex_tests = array(
          '[0-9]+' => 'Gebruik tenminste één cijfer in het wachtwoord',
          '[a-z]+' => 'Gebruik tenminste één kleine letter in het wachtwoord',
          '[A-Z]+' => 'Gebruik tenminste één hoofdletter in het wachtwoord',
          '\W+' => 'Gebruik tenminste één teken (bijv. !?+-= e.d.) in het wachtwoord',
        );
        foreach ($regex_tests as $regex => $feedback) {
          if (!preg_match('/' . $regex . '/', $values['pass_reset'])) {
            $pass_feedback_array[] = $feedback;
            $error = TRUE;
            $pass_error = TRUE;
          }
        }
        if (strlen($values['pass_reset']) < 6) {
          $pass_feedback_array[] = 'Het wachtwoord moet minimaal 6 tekens lang zijn';
          $error = TRUE;
          $pass_error = TRUE;
        }
        if (!empty($pass_error)) {
          $pass_feedback = implode('<br/>', $pass_feedback_array);
          form_set_error('pass_reset', $pass_feedback);
        }
        break;

      case 'no_account':
        preg_match('/^([1-9][0-9]{3})[\s]?([A-Za-z]{2})$/', $values['postal_code'], $matches); 
        $postal_code = $matches[1] . ' ' . strtoupper($matches[2]);
        $values['postal_code'] = $postal_code;

        if (!preg_match('/^[1-9][0-9]{3}[\s]?[A-Za-z]{2}$/', $values['postal_code'])) {
          form_set_error('postal_code', 'Vul een geldige postcode in!');
        }
        if (empty($values['birth_date'])) {
          form_set_error('birth_date', 'Vul je geboortedatum in!');
        }
        break;

      case 'recheck_id':
        if (filter_var($values['new_contact_id'], FILTER_VALIDATE_INT) === FALSE) {
          form_set_error('new_contact_id', 'Vul een geldig relatie -of lidnummer in');
        }
        break;

      case 'account_not_verified':
        if (empty($values['first_name'])) {
          form_set_error('first_name', 'Vul je voornaam in!');
        }
        if (empty($values['last_name'])) {
          form_set_error('last_name', 'Vul je achternaam in!');
        }
        if (empty($values['birth_date'])) {
          form_set_error('birth_date', 'Vul je geboortedatum in!');
        }
        if (empty($values['street_and_number'])) {
          form_set_error('street_and_number', 'Vul je adres in!');
        }
        if (!preg_match('/^[1-9][0-9]{3}[\s]?[A-Za-z]{2}$/', $values['postal_code'])) {
          form_set_error('postal_code', 'Vul een geldige postcode in!');
        }
        if (empty($values['locality'])) {
          form_set_error('locality', 'Vul je woonplaats in!');
        }
        if (!valid_email_address($values['email'])) {
          form_set_error('email', 'Vul een geldig e-mailadres in!');
        }
        $regex_telephone_fixed = '/^(((0)[1-9]{2}[0-9][-]?[1-9][0-9]{5})|((\\+31|0|0031)[1-9][0-9][-]?[1-9][0-9]{6}))$/';
        $regex_telephone_mobile = '/^(((\\+31|0|0031)6){1}[1-9]{1}[0-9]{7})$/';
        if (!(preg_match($regex_telephone_fixed, $values['telephone']) || preg_match($regex_telephone_mobile, $values['telephone']))) {
          form_set_error('telephone', 'Vul een geldig telefoonnummer in!');
        }
        break;

      case 'email_check':
        break;

      case 'new_email':
        if (!valid_email_address($values['new_email'])) {
          form_set_error('new_email', 'Vul een geldig e-mailadres in!');
        }
        break;

      case 'new_pass':
        // Validate password.
        $regex_tests = array(
          '[0-9]+' => 'Gebruik tenminste één cijfer in het wachtwoord',
          '[a-z]+' => 'Gebruik tenminste één kleine letter in het wachtwoord',
          '[A-Z]+' => 'Gebruik tenminste één hoofdletter in het wachtwoord',
          '\W+' => 'Gebruik tenminste één teken (bijv. !?+-= e.d.) in het wachtwoord',
        );
        foreach ($regex_tests as $regex => $feedback) {
          if (!preg_match('/' . $regex . '/', $values['new_pass'])) {
            $pass_feedback_array[] = $feedback;
            $error = TRUE;
            $pass_error = TRUE;
          }
        }
        if (strlen($values['new_pass']) < 6) {
          $pass_feedback_array[] = 'Het wachtwoord moet minimaal 6 tekens lang zijn';
          $error = TRUE;
          $pass_error = TRUE;
        }
        if (!empty($pass_error)) {
          $pass_feedback = implode('<br/>', $pass_feedback_array);
          form_set_error('new_pass', $pass_feedback);
        }
        break;

      }

      break;

    case 'no_id_button':
      break;

    case 'pass_reset_button':
      break;

    case 'back_button':
      break;

    }
  }
}

function splogin_login_form_submit($form, &$form_state) {

  if (isset($form_state['triggering_element'])) {

    $values = $form_state['values'];
    $stored_data = &$form_state['stored_data'];
    $stages = &$form_state['stages'];
    $stage = end($form_state['stages']);

    $trigger = $form_state['triggering_element']['#name'];

    switch ($trigger) {

    case 'general_submit_button':
      switch ($stage) {

      case 'start':
        if (splogin_get_civi_contact($values['contact_id'])) {
          $stored_data['contact_id'] = $values['contact_id'];
          $drupal_account = splogin_drupal_account_exists($stored_data['contact_id']);
          if ($drupal_account !== FALSE) {
            $stored_data['drupal_account'] = $drupal_account;
            $stages[] = 'has_account';
          }
          else {
            unset($stored_data['drupal_account']);
            $stages[] = 'no_account';
          }
        }
        else {
          drupal_set_message('Het relatie- lidnummer is niet correct', 'error');
        }
        break;

      case 'no_id':
        splogin_process_id_request($values);
        return;
        break;

      case 'has_account':
        if (splogin_get_civi_contact($values['contact_id'])) {
          $drupal_account = splogin_drupal_account_exists($stored_data['contact_id']);
          if ($drupal_account === FALSE) {
            unset($stored_data['drupal_account']);
            $stages[] = 'no_account';
          }
          else {
            global $user;
            $user = user_load($drupal_account);
            user_login_finalize($user);
            drupal_goto();
          }
        }
        else {
          drupal_set_message('Het wachtwoord of relatie- lidnummer is niet correct', 'error');
        }
        break;

      case 'no_account':
        $stored_data['postal_code'] = $values['postal_code'];
        $stored_data['birth_date'] = $values['birth_date'];
        $result = splogin_verify_civi_user($stored_data['contact_id'], $values['postal_code'], $values['birth_date']);
        if ($result === FALSE) {
          $stages[] = 'recheck_id';
        }
        elseif ($result === 'contact_valid_no_email') {
          $stages[] = 'new_email';
        }
        else {
          $stored_data['email_check'] = $result;
          $stages[] = 'email_check';
        }

        break;

      case 'recheck_id':
        if ($values['new_contact_id'] !== $stored_data['contact_id']) {
          $stored_data['contact_id'] = $values['new_contact_id'];
          if (splogin_get_civi_contact($stored_data['contact_id'])) {
            $drupal_account = splogin_drupal_account_exists($stored_data['contact_id']);
            if ($drupal_account !== FALSE) {
              $stored_data['drupal_account'] = $drupal_account;
              $stages[] = 'has_account';
            }
            else {
              unset($stored_data['drupal_account']);
              $stages[] = 'no_account';
            }
          }
          else {
            drupal_set_message('Dit relatie- of lidnummer is niet correct');
            $stages = array();
            $stages[] = 'start';
          }
        }
        else {
          $stages[] = 'account_not_verified';
        }
        break;

      case 'email_check':
        if ($values['email_correct']['correct'] === 'correct') {
          $stored_data['email'] = $stored_data['email_check'];
          splogin_new_create_account($stored_data);
          return;
        }
        else {
          $stages[] = 'new_email';
        }
        break;

      case 'new_email':
        $stored_data['email'] = $values['new_email'];
        splogin_new_civi_email($stored_data);
        splogin_new_create_account($stored_data);
        return;
        break;

      case 'account_not_verified':
        return;
        break;
      }

      break;

    case 'no_id_button':
      $stages[] = 'no_id';
      break;

    case 'no_member_button':
      drupal_goto('aanmelden/lid');
      break;

    case 'pass_reset_button':
      global $language;
      $account = user_load($stored_data['drupal_account']);
      if (!empty($account)) {
        // Mail one time login URL and instructions using current language.
        $mail = _user_mail_notify('password_reset', $account, $language);
        if (!empty($mail)) {
          watchdog('user', 'Password reset instructions mailed to %name at %email.', array('%name' => $account->name, '%email' => $account->mail));
          drupal_set_message(t('Further instructions have been sent to your e-mail address.'));
        }
      }
      return;
      break;

    case 'back_button':
      array_pop($stages);
      break;

    }
  }

  $form_state['rebuild'] = TRUE;
}
